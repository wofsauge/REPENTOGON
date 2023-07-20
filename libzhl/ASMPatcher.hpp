#pragma once

#include <array>
#include <atomic>
#include <bitset>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>

#include <Windows.h>

#include <Zydis/Zydis.h>

#include "libzhl.h"

#define X86_LONGEST_INSTRUCTION_NBYTES 15

class LIBZHL_API ASMPatcher
{
public:
	enum class CondJumps {
		JO,
		JNO,
		JB, JNAE = JB, JC = JB,
		JNB, JAE = JNB, JNC = JNB,
		JZ, JE = JZ,
		JNZ, JNE = JNZ,
		JBE, JNA = JBE,
		JNBE, JA = JNBE,
		JS,
		JNS,
		JP, JPE = JP,
		JNP, JPO = JNP,
		JL, JNGE = JL,
		JNL, JGE = JNL,
		JLE, JNG = JLE,
		JNLE, JG = JNLE
	};

	class ProtectionGuard {
	public:
		ProtectionGuard(void* page, DWORD in, DWORD out = 0);
		~ProtectionGuard();

	private:
		void* _page;
		DWORD _in;
		DWORD _out;
	};

	friend class ProtectionGuard;
	friend class ASMPatch;

	static constexpr const size_t PAGE_SIZE = 4096;
	~ASMPatcher();

	ASMPatcher(const ASMPatcher&) = delete;
	ASMPatcher(ASMPatcher&&) = delete;
	ASMPatcher& operator=(ASMPatcher const&) = delete;
	ASMPatcher& operator=(ASMPatcher&&) = delete;

	static ASMPatcher& instance();

	void* AttemptPatchFunction(const char* beginSig, const char* endSig, const char* patchSig, const char* with);
	void* PatchFromSig(const char* sig, const char* with);
	void* PatchAt(void* at, const char* with, size_t len = 0);
	void* PatchAt(void* at, ASMPatch* with);
	void* Patch(void* at, void* page, const char* with, size_t len);

	static ptrdiff_t JumpOffset(const void* next, const void* target);
	static std::unique_ptr<char[]> EncodeJump(const void* at, const void* target);
	static void* EncodeAndWriteJump(void* at, const void* target);
	static std::unique_ptr<char[]> EncodeCondJump(CondJumps cond, const void* at, const void* target);

	static void SetExecutable(char* text);

	template<typename T>
	static std::enable_if_t<std::is_integral_v<T>> EndianConvert(T* t) {
		auto swap = [](uint8_t& a, uint8_t& b) -> void {
			uint8_t c = a;
			a = b;
			b = c;
		};

		uint8_t* ptr = (uint8_t*)t;
		if constexpr (sizeof(T) == 1) {
			return;
		} else if constexpr (sizeof(T) == 2) {
			swap(ptr[0], ptr[1]);
		}
		else if constexpr (sizeof(T) == 4) {
			swap(ptr[0], ptr[3]);
			swap(ptr[1], ptr[2]);
		}
	}

private:
	ASMPatcher();

	// Page will always be allocated with read and write, but never execute.
	// This function CANNOT return NULL.
	void* AllocPage();

	// Return either an existing page, or a new page if writing the patch would 
	// go out of the bounds of the last allocated page. 
	// The returned page will always have at least read and write privileges.
	// If withExecute is set to false, the page will not have execute permission 
	// regardless of its original protection. If withExecute is set to true, 
	// the page will have execute permission, regardless of its original protection.
	// By construction, both these functions CANNOT return NULL.
	void* GetAllocPage(const char* text, bool withExecute);
	void* GetAllocPage(size_t n, bool withExecute);

	static DWORD SetProtection(void* page, DWORD protect);
	static void GetMemoryInformation(void* page, PMEMORY_BASIC_INFORMATION infos);
	static DWORD Protect(PMEMORY_BASIC_INFORMATION const infos, DWORD protect);

	// __declspec(noreturn) void Error(const char* fmt, ...);

	std::vector<void*> _pages;
	void* _firstAvailable = nullptr;
	size_t _bytesRemaining = 0;

	std::atomic<bool> _patching;
};

class LIBZHL_API ASMPatch
{
public:
	class LIBZHL_API ByteBuffer {
	public:
		ByteBuffer();

		// Deep copy. Costly but allows multiple independant copies.
		ByteBuffer(ByteBuffer const& other);
		ByteBuffer& operator=(const ByteBuffer& other);

		// Transfer ownership. Faster, but the source object is reset
		ByteBuffer(ByteBuffer&& other);
		ByteBuffer& operator=(ByteBuffer&& other);

		ByteBuffer& AddString(const char* s);
		ByteBuffer& AddZeroes(uint32_t n);
		ByteBuffer& AddAny(const char* addr, size_t n);
		ByteBuffer& AddByteBuffer(ByteBuffer const& other);

		size_t GetSize() const;
		char* GetData() const;

		void Dump(FILE* f);

	private:
		void CheckAndResize(size_t s);

		std::unique_ptr<char[]> _data;
		size_t _capacity, _size;
	};

	/* Convert an integer to its hex representation as a string, performing
	 * a zero extension. 
	 * 
	 * For 16 and 32 bits versions, endianConvert can be used to flip the bytes of
	 * the result if needed. 
	 */
	static ByteBuffer ToHexString(int8_t x);
	static ByteBuffer ToHexString(int16_t x, bool endianConvert);
	static ByteBuffer ToHexString(int32_t x, bool endianConvert);

	ASMPatch();
	ASMPatch(const ASMPatch& other) = delete;
	ASMPatch& operator=(const ASMPatch& other) = delete;

	class LIBZHL_API SavedRegisters {
	public:
		enum Registers {
			EAX = 1 << 0,
			EBX = 1 << 1,
			ECX = 1 << 2,
			EDX = 1 << 3,
			ESI = 1 << 4,
			EDI = 1 << 5,
			ESP = 1 << 6,
			EBP = 1 << 7,
			GP_REGISTERS_STACKLESS = EAX | EBX | ECX | EDX | ESI | EDI,
			GP_REGISTERS = GP_REGISTERS_STACKLESS | ESP | EBP,
			XMM0 = 1 << 8,
			XMM1 = 1 << 9,
			XMM2 = 1 << 10,
			XMM3 = 1 << 11,
			XMM4 = 1 << 12,
			XMM5 = 1 << 13,
			XMM6 = 1 << 14,
			XMM7 = 1 << 15
		};

		SavedRegisters(uint32_t mask, bool shouldRestore);
		~SavedRegisters();

	private:
		friend ASMPatch;
		friend BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID);

		void Restore();
		uint32_t GetMask() const;

		bool _shouldRestore;
		bool _restored = false;
		uint32_t _mask;

		static void _Init();
		static std::map<uint32_t, ASMPatch::ByteBuffer> _RegisterPushMap;
		static std::map<uint32_t, ASMPatch::ByteBuffer> _RegisterPopMap;
		static std::array<uint32_t, 16> _RegisterOrder;
	};

	enum class Registers {
		EAX,
		EBX,
		ECX,
		EDX,
		ESI,
		EDI,
		ESP,
		EBP
	};

	enum class LeaOps {
		PLUS,
		MULT
	};

	/* Add arbitrary bytes to the patch. These bytes cannot contain a null character
	 * as it will cause the copy of the bytes into the patch to stop early.
	 */
	ASMPatch& AddBytes(std::string const& str);
	/* Add arbtirary bytes to the patch. These bytes can contain null characters. */
	ASMPatch& AddBytes(ByteBuffer const& str);
	ASMPatch& AddZeroes(uint32_t n = 1);
	ASMPatch& AddRelativeJump(void* target);
	ASMPatch& AddConditionalRelativeJump(ASMPatcher::CondJumps cond, void* target);
	/* Move a value from memory into a register. Memory access is performed through 
	 * a register. This allows moves of the form "mov dst, [src + offset]".
	 */
	ASMPatch& MoveFromMemory(Registers src, int32_t offset, Registers dst);
	/* Move a value from a register into memory. Memory access is performed through 
	 * a register. This allows moves of the form "mov dst, [src + offset]".
	 */
	ASMPatch& MoveToMemory(Registers src, int32_t offset, Registers dst);
	
	/* typedef std::variant<Registers, int32_t> LeaOperand;
	typedef std::tuple<LeaOps, LeaOperand> LeaParameter;
	ASMPatch& LoadEffectiveAddress(Registers dst, Registers src, std::optional<LeaParameter> firstParam, std::optional<LeaParameter> secondParam); */
	ASMPatch& LoadEffectiveAddress(Registers src, int32_t offset, Registers dst);
	ASMPatch& PreserveRegisters(SavedRegisters& registers);
	ASMPatch& RestoreRegisters(SavedRegisters& registers);
	ASMPatch& Push(Registers reg);
	ASMPatch& Pop(Registers reg);
	/* Add a call instruction. The jump is relative and uses the 0xE8 opcode for the 
	 * call instruction. Registers are not preserved: you must take care of that yourself.
	 * 
	 * addr is the address of the function to call.
	 */
	ASMPatch& AddInternalCall(void* addr);
	ASMPatch& AddDLLCall(void* addr);

	size_t Length() const;
	std::unique_ptr<char[]> ToASM(void* at) const;

private:
	class LIBZHL_API ASMNode {
	public:
		virtual std::unique_ptr<char[]> ToASM(void* at) const = 0;
		virtual size_t Length() const = 0;
	};

	class LIBZHL_API ASMBytesAny : public ASMNode {
	public:
		ASMBytesAny(ByteBuffer const& bytes);
		std::unique_ptr<char[]> ToASM(void*) const override;
		size_t Length() const override;

	private:
		ByteBuffer _bytes;
	};

	class LIBZHL_API ASMBytes : public ASMNode {
	public:
		ASMBytes(const char* bytes);
		std::unique_ptr<char[]> ToASM(void*) const override;
		size_t Length() const override;

	private:
		std::unique_ptr<char[]> _bytes;
	};

	class LIBZHL_API ASMZeroes : public ASMNode {
	public:
		ASMZeroes(uint32_t n);
		std::unique_ptr<char[]> ToASM(void* at) const override;
		size_t Length() const override;

	private:
		uint32_t _n;
	};

	class LIBZHL_API ASMJump : public ASMNode {
	public:
		ASMJump(void* target);
		std::unique_ptr<char[]> ToASM(void* at) const override;
		size_t Length() const override;

	private:
		void* _target;
	};

	class LIBZHL_API ASMCondJump : public ASMNode {
	public:
		ASMCondJump(ASMPatcher::CondJumps cond, void* target);
		std::unique_ptr<char[]> ToASM(void* at) const override;
		size_t Length() const override;

	private:
		ASMPatcher::CondJumps _cond;
		void* _target;
	};

	class LIBZHL_API ASMInternalCall : public ASMNode {
	public:
		ASMInternalCall(void* target);
		std::unique_ptr<char[]> ToASM(void* at) const override;
		size_t Length() const override;

	private:
		void* _target;
	};

	friend BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID);
	static void _Init();

	// friend void* ASMPatcher::PatchAt(void*, const char*);

	std::vector<std::unique_ptr<ASMNode>> _nodes;
	static std::map<ASMPatch::Registers, std::bitset<8>> _ModRM;
	static uint32_t RegisterToBackupRegister(Registers reg);
	size_t _size = 0;
};

/// Box a type, preventing Visual Studio from moving a value of such a type in a register.
/// Only works on fundamental types (char, int, float, pointers).
template<typename T>
struct Box {
	std::enable_if_t<std::disjunction_v<std::is_fundamental<T>, std::is_pointer<T>>, T> _t;

	T& Get() {
		return _t;
	}

	T const& Get() const {
		return _t;
	}
};

#define sASMPatcher ASMPatcher::instance()