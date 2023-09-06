
// Generated from ZHLLexer.g4 by ANTLR 4.12.0


#include "ZHLLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct ZHLLexerStaticData final {
  ZHLLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ZHLLexerStaticData(const ZHLLexerStaticData&) = delete;
  ZHLLexerStaticData(ZHLLexerStaticData&&) = delete;
  ZHLLexerStaticData& operator=(const ZHLLexerStaticData&) = delete;
  ZHLLexerStaticData& operator=(ZHLLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag zhllexerLexerOnceFlag;
ZHLLexerStaticData *zhllexerLexerStaticData = nullptr;

void zhllexerLexerInitialize() {
  assert(zhllexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<ZHLLexerStaticData>(
    std::vector<std::string>{
      "DoubleQuote", "Colon", "Semi", "Qualifier", "Cleanup", "Static", 
      "Virtual", "Declspec", "External", "LeftParen", "RightParen", "Comma", 
      "Star", "Lt", "Gt", "LeftRBracket", "RightRBracket", "LeftBracket", 
      "RightBracket", "Class", "Struct", "Reference", "Depends", "Typedef", 
      "Const", "CppRef", "Unsigned", "Signed", "Long", "Int", "Short", "Char", 
      "Bool", "Float", "Double", "Void", "Type", "Size", "Synonym", "Align", 
      "Vtable", "Skip", "Pure", "Override", "Visibility", "Public", "Private", 
      "Protected", "Register", "GeneralPurposeRegister", "Eax", "Ebx", "Ecx", 
      "Edx", "Esi", "Edi", "Esp", "Ebp", "SSERegister", "Xmm0", "Xmm1", 
      "Xmm2", "Xmm3", "Xmm4", "Xmm5", "Xmm6", "Xmm7", "CallingConvention", 
      "Stdcall", "Cdecl", "Fastcall", "Thiscall", "Signature", "ReferenceSignature", 
      "Operator", "OpSymbol", "Name", "Number", "HexNumber", "DecNumber", 
      "GenericCode", "Whitespace", "Newline", "BlockComment", "LineComment", 
      "Any"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'\"'", "':'", "';'", "", "'cleanup'", "'static'", "'virtual'", 
      "'__declspec'", "'external'", "'('", "')'", "','", "'*'", "'<'", "'>'", 
      "'['", "']'", "'{'", "'}'", "'class'", "'struct'", "'reference'", 
      "'depends'", "'typedef'", "'const'", "'&'", "'unsigned'", "'signed'", 
      "'long'", "'int'", "'short'", "'char'", "'bool'", "'float'", "'double'", 
      "'void'", "'TypeInfo'", "'Size'", "'Synonym'", "'Align'", "'__vtable'", 
      "'skip'", "'pure'", "'override'", "", "'public'", "'private'", "'protected'", 
      "", "", "'eax'", "'ebx'", "'ecx'", "'edx'", "'esi'", "'edi'", "'esp'", 
      "'ebp'", "", "'xmm0'", "'xmm1'", "'xmm2'", "'xmm3'", "'xmm4'", "'xmm5'", 
      "'xmm6'", "'xmm7'", "", "'__stdcall'", "'__cdecl'", "'__fastcall'", 
      "'__thiscall'", "", "", "'operator'"
    },
    std::vector<std::string>{
      "", "DoubleQuote", "Colon", "Semi", "Qualifier", "Cleanup", "Static", 
      "Virtual", "Declspec", "External", "LeftParen", "RightParen", "Comma", 
      "Star", "Lt", "Gt", "LeftRBracket", "RightRBracket", "LeftBracket", 
      "RightBracket", "Class", "Struct", "Reference", "Depends", "Typedef", 
      "Const", "CppRef", "Unsigned", "Signed", "Long", "Int", "Short", "Char", 
      "Bool", "Float", "Double", "Void", "Type", "Size", "Synonym", "Align", 
      "Vtable", "Skip", "Pure", "Override", "Visibility", "Public", "Private", 
      "Protected", "Register", "GeneralPurposeRegister", "Eax", "Ebx", "Ecx", 
      "Edx", "Esi", "Edi", "Esp", "Ebp", "SSERegister", "Xmm0", "Xmm1", 
      "Xmm2", "Xmm3", "Xmm4", "Xmm5", "Xmm6", "Xmm7", "CallingConvention", 
      "Stdcall", "Cdecl", "Fastcall", "Thiscall", "Signature", "ReferenceSignature", 
      "Operator", "OpSymbol", "Name", "Number", "HexNumber", "DecNumber", 
      "GenericCode", "Whitespace", "Newline", "BlockComment", "LineComment", 
      "Any"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,86,703,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,
  	7,70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,
  	7,77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,
  	7,84,2,85,7,85,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,3,1,3,3,3,184,8,3,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,
  	13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,
  	19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,
  	22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,
  	30,1,30,1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,
  	32,1,32,1,33,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,34,1,
  	34,1,35,1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,
  	36,1,37,1,37,1,37,1,37,1,37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,
  	39,1,39,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,
  	40,1,41,1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,43,1,43,1,43,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,44,1,44,1,44,3,44,414,8,44,1,45,1,45,1,
  	45,1,45,1,45,1,45,1,45,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,47,1,
  	47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,48,1,48,3,48,443,8,48,1,
  	49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,3,49,453,8,49,1,50,1,50,1,50,1,
  	50,1,51,1,51,1,51,1,51,1,52,1,52,1,52,1,52,1,53,1,53,1,53,1,53,1,54,1,
  	54,1,54,1,54,1,55,1,55,1,55,1,55,1,56,1,56,1,56,1,56,1,57,1,57,1,57,1,
  	57,1,58,1,58,1,58,1,58,1,58,1,58,1,58,1,58,3,58,495,8,58,1,59,1,59,1,
  	59,1,59,1,59,1,60,1,60,1,60,1,60,1,60,1,61,1,61,1,61,1,61,1,61,1,62,1,
  	62,1,62,1,62,1,62,1,63,1,63,1,63,1,63,1,63,1,64,1,64,1,64,1,64,1,64,1,
  	65,1,65,1,65,1,65,1,65,1,66,1,66,1,66,1,66,1,66,1,67,1,67,1,67,1,67,3,
  	67,541,8,67,1,68,1,68,1,68,1,68,1,68,1,68,1,68,1,68,1,68,1,68,1,69,1,
  	69,1,69,1,69,1,69,1,69,1,69,1,69,1,70,1,70,1,70,1,70,1,70,1,70,1,70,1,
  	70,1,70,1,70,1,70,1,71,1,71,1,71,1,71,1,71,1,71,1,71,1,71,1,71,1,71,1,
  	71,1,72,1,72,3,72,585,8,72,1,72,4,72,588,8,72,11,72,12,72,589,1,72,1,
  	72,1,72,1,73,1,73,3,73,597,8,73,1,73,4,73,600,8,73,11,73,12,73,601,1,
  	73,1,73,1,73,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,74,1,75,1,75,3,
  	75,618,8,75,1,75,1,75,1,75,3,75,623,8,75,1,76,1,76,5,76,627,8,76,10,76,
  	12,76,630,9,76,1,77,1,77,3,77,634,8,77,1,78,1,78,1,78,1,78,4,78,640,8,
  	78,11,78,12,78,641,1,79,4,79,645,8,79,11,79,12,79,646,1,80,1,80,1,80,
  	1,80,5,80,653,8,80,10,80,12,80,656,9,80,1,80,1,80,1,80,1,81,4,81,662,
  	8,81,11,81,12,81,663,1,81,1,81,1,82,1,82,3,82,670,8,82,1,82,3,82,673,
  	8,82,1,82,1,82,1,83,1,83,1,83,1,83,5,83,681,8,83,10,83,12,83,684,9,83,
  	1,83,1,83,1,83,1,83,1,83,1,84,1,84,1,84,1,84,5,84,695,8,84,10,84,12,84,
  	698,9,84,1,84,1,84,1,85,1,85,2,654,682,0,86,1,1,3,2,5,3,7,4,9,5,11,6,
  	13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,
  	37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,
  	30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,40,81,41,
  	83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,49,99,50,101,51,103,52,105,
  	53,107,54,109,55,111,56,113,57,115,58,117,59,119,60,121,61,123,62,125,
  	63,127,64,129,65,131,66,133,67,135,68,137,69,139,70,141,71,143,72,145,
  	73,147,74,149,75,151,76,153,77,155,78,157,79,159,80,161,81,163,82,165,
  	83,167,84,169,85,171,86,1,0,9,4,0,48,57,63,63,65,70,97,102,5,0,40,41,
  	48,57,63,63,65,70,97,102,3,0,42,43,45,45,47,47,3,0,65,90,95,95,97,122,
  	4,0,48,57,65,90,95,95,97,122,3,0,48,57,65,70,97,102,1,0,48,57,2,0,9,9,
  	32,32,2,0,10,10,13,13,742,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,
  	0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,
  	51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,
  	0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,
  	0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,
  	83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,
  	0,0,0,0,95,1,0,0,0,0,97,1,0,0,0,0,99,1,0,0,0,0,101,1,0,0,0,0,103,1,0,
  	0,0,0,105,1,0,0,0,0,107,1,0,0,0,0,109,1,0,0,0,0,111,1,0,0,0,0,113,1,0,
  	0,0,0,115,1,0,0,0,0,117,1,0,0,0,0,119,1,0,0,0,0,121,1,0,0,0,0,123,1,0,
  	0,0,0,125,1,0,0,0,0,127,1,0,0,0,0,129,1,0,0,0,0,131,1,0,0,0,0,133,1,0,
  	0,0,0,135,1,0,0,0,0,137,1,0,0,0,0,139,1,0,0,0,0,141,1,0,0,0,0,143,1,0,
  	0,0,0,145,1,0,0,0,0,147,1,0,0,0,0,149,1,0,0,0,0,151,1,0,0,0,0,153,1,0,
  	0,0,0,155,1,0,0,0,0,157,1,0,0,0,0,159,1,0,0,0,0,161,1,0,0,0,0,163,1,0,
  	0,0,0,165,1,0,0,0,0,167,1,0,0,0,0,169,1,0,0,0,0,171,1,0,0,0,1,173,1,0,
  	0,0,3,175,1,0,0,0,5,177,1,0,0,0,7,183,1,0,0,0,9,185,1,0,0,0,11,193,1,
  	0,0,0,13,200,1,0,0,0,15,208,1,0,0,0,17,219,1,0,0,0,19,228,1,0,0,0,21,
  	230,1,0,0,0,23,232,1,0,0,0,25,234,1,0,0,0,27,236,1,0,0,0,29,238,1,0,0,
  	0,31,240,1,0,0,0,33,242,1,0,0,0,35,244,1,0,0,0,37,246,1,0,0,0,39,248,
  	1,0,0,0,41,254,1,0,0,0,43,261,1,0,0,0,45,271,1,0,0,0,47,279,1,0,0,0,49,
  	287,1,0,0,0,51,293,1,0,0,0,53,295,1,0,0,0,55,304,1,0,0,0,57,311,1,0,0,
  	0,59,316,1,0,0,0,61,320,1,0,0,0,63,326,1,0,0,0,65,331,1,0,0,0,67,336,
  	1,0,0,0,69,342,1,0,0,0,71,349,1,0,0,0,73,354,1,0,0,0,75,363,1,0,0,0,77,
  	368,1,0,0,0,79,376,1,0,0,0,81,382,1,0,0,0,83,391,1,0,0,0,85,396,1,0,0,
  	0,87,401,1,0,0,0,89,413,1,0,0,0,91,415,1,0,0,0,93,422,1,0,0,0,95,430,
  	1,0,0,0,97,442,1,0,0,0,99,452,1,0,0,0,101,454,1,0,0,0,103,458,1,0,0,0,
  	105,462,1,0,0,0,107,466,1,0,0,0,109,470,1,0,0,0,111,474,1,0,0,0,113,478,
  	1,0,0,0,115,482,1,0,0,0,117,494,1,0,0,0,119,496,1,0,0,0,121,501,1,0,0,
  	0,123,506,1,0,0,0,125,511,1,0,0,0,127,516,1,0,0,0,129,521,1,0,0,0,131,
  	526,1,0,0,0,133,531,1,0,0,0,135,540,1,0,0,0,137,542,1,0,0,0,139,552,1,
  	0,0,0,141,560,1,0,0,0,143,571,1,0,0,0,145,582,1,0,0,0,147,594,1,0,0,0,
  	149,606,1,0,0,0,151,622,1,0,0,0,153,624,1,0,0,0,155,633,1,0,0,0,157,635,
  	1,0,0,0,159,644,1,0,0,0,161,648,1,0,0,0,163,661,1,0,0,0,165,672,1,0,0,
  	0,167,676,1,0,0,0,169,690,1,0,0,0,171,701,1,0,0,0,173,174,5,34,0,0,174,
  	2,1,0,0,0,175,176,5,58,0,0,176,4,1,0,0,0,177,178,5,59,0,0,178,6,1,0,0,
  	0,179,184,3,9,4,0,180,184,3,11,5,0,181,184,3,13,6,0,182,184,3,15,7,0,
  	183,179,1,0,0,0,183,180,1,0,0,0,183,181,1,0,0,0,183,182,1,0,0,0,184,8,
  	1,0,0,0,185,186,5,99,0,0,186,187,5,108,0,0,187,188,5,101,0,0,188,189,
  	5,97,0,0,189,190,5,110,0,0,190,191,5,117,0,0,191,192,5,112,0,0,192,10,
  	1,0,0,0,193,194,5,115,0,0,194,195,5,116,0,0,195,196,5,97,0,0,196,197,
  	5,116,0,0,197,198,5,105,0,0,198,199,5,99,0,0,199,12,1,0,0,0,200,201,5,
  	118,0,0,201,202,5,105,0,0,202,203,5,114,0,0,203,204,5,116,0,0,204,205,
  	5,117,0,0,205,206,5,97,0,0,206,207,5,108,0,0,207,14,1,0,0,0,208,209,5,
  	95,0,0,209,210,5,95,0,0,210,211,5,100,0,0,211,212,5,101,0,0,212,213,5,
  	99,0,0,213,214,5,108,0,0,214,215,5,115,0,0,215,216,5,112,0,0,216,217,
  	5,101,0,0,217,218,5,99,0,0,218,16,1,0,0,0,219,220,5,101,0,0,220,221,5,
  	120,0,0,221,222,5,116,0,0,222,223,5,101,0,0,223,224,5,114,0,0,224,225,
  	5,110,0,0,225,226,5,97,0,0,226,227,5,108,0,0,227,18,1,0,0,0,228,229,5,
  	40,0,0,229,20,1,0,0,0,230,231,5,41,0,0,231,22,1,0,0,0,232,233,5,44,0,
  	0,233,24,1,0,0,0,234,235,5,42,0,0,235,26,1,0,0,0,236,237,5,60,0,0,237,
  	28,1,0,0,0,238,239,5,62,0,0,239,30,1,0,0,0,240,241,5,91,0,0,241,32,1,
  	0,0,0,242,243,5,93,0,0,243,34,1,0,0,0,244,245,5,123,0,0,245,36,1,0,0,
  	0,246,247,5,125,0,0,247,38,1,0,0,0,248,249,5,99,0,0,249,250,5,108,0,0,
  	250,251,5,97,0,0,251,252,5,115,0,0,252,253,5,115,0,0,253,40,1,0,0,0,254,
  	255,5,115,0,0,255,256,5,116,0,0,256,257,5,114,0,0,257,258,5,117,0,0,258,
  	259,5,99,0,0,259,260,5,116,0,0,260,42,1,0,0,0,261,262,5,114,0,0,262,263,
  	5,101,0,0,263,264,5,102,0,0,264,265,5,101,0,0,265,266,5,114,0,0,266,267,
  	5,101,0,0,267,268,5,110,0,0,268,269,5,99,0,0,269,270,5,101,0,0,270,44,
  	1,0,0,0,271,272,5,100,0,0,272,273,5,101,0,0,273,274,5,112,0,0,274,275,
  	5,101,0,0,275,276,5,110,0,0,276,277,5,100,0,0,277,278,5,115,0,0,278,46,
  	1,0,0,0,279,280,5,116,0,0,280,281,5,121,0,0,281,282,5,112,0,0,282,283,
  	5,101,0,0,283,284,5,100,0,0,284,285,5,101,0,0,285,286,5,102,0,0,286,48,
  	1,0,0,0,287,288,5,99,0,0,288,289,5,111,0,0,289,290,5,110,0,0,290,291,
  	5,115,0,0,291,292,5,116,0,0,292,50,1,0,0,0,293,294,5,38,0,0,294,52,1,
  	0,0,0,295,296,5,117,0,0,296,297,5,110,0,0,297,298,5,115,0,0,298,299,5,
  	105,0,0,299,300,5,103,0,0,300,301,5,110,0,0,301,302,5,101,0,0,302,303,
  	5,100,0,0,303,54,1,0,0,0,304,305,5,115,0,0,305,306,5,105,0,0,306,307,
  	5,103,0,0,307,308,5,110,0,0,308,309,5,101,0,0,309,310,5,100,0,0,310,56,
  	1,0,0,0,311,312,5,108,0,0,312,313,5,111,0,0,313,314,5,110,0,0,314,315,
  	5,103,0,0,315,58,1,0,0,0,316,317,5,105,0,0,317,318,5,110,0,0,318,319,
  	5,116,0,0,319,60,1,0,0,0,320,321,5,115,0,0,321,322,5,104,0,0,322,323,
  	5,111,0,0,323,324,5,114,0,0,324,325,5,116,0,0,325,62,1,0,0,0,326,327,
  	5,99,0,0,327,328,5,104,0,0,328,329,5,97,0,0,329,330,5,114,0,0,330,64,
  	1,0,0,0,331,332,5,98,0,0,332,333,5,111,0,0,333,334,5,111,0,0,334,335,
  	5,108,0,0,335,66,1,0,0,0,336,337,5,102,0,0,337,338,5,108,0,0,338,339,
  	5,111,0,0,339,340,5,97,0,0,340,341,5,116,0,0,341,68,1,0,0,0,342,343,5,
  	100,0,0,343,344,5,111,0,0,344,345,5,117,0,0,345,346,5,98,0,0,346,347,
  	5,108,0,0,347,348,5,101,0,0,348,70,1,0,0,0,349,350,5,118,0,0,350,351,
  	5,111,0,0,351,352,5,105,0,0,352,353,5,100,0,0,353,72,1,0,0,0,354,355,
  	5,84,0,0,355,356,5,121,0,0,356,357,5,112,0,0,357,358,5,101,0,0,358,359,
  	5,73,0,0,359,360,5,110,0,0,360,361,5,102,0,0,361,362,5,111,0,0,362,74,
  	1,0,0,0,363,364,5,83,0,0,364,365,5,105,0,0,365,366,5,122,0,0,366,367,
  	5,101,0,0,367,76,1,0,0,0,368,369,5,83,0,0,369,370,5,121,0,0,370,371,5,
  	110,0,0,371,372,5,111,0,0,372,373,5,110,0,0,373,374,5,121,0,0,374,375,
  	5,109,0,0,375,78,1,0,0,0,376,377,5,65,0,0,377,378,5,108,0,0,378,379,5,
  	105,0,0,379,380,5,103,0,0,380,381,5,110,0,0,381,80,1,0,0,0,382,383,5,
  	95,0,0,383,384,5,95,0,0,384,385,5,118,0,0,385,386,5,116,0,0,386,387,5,
  	97,0,0,387,388,5,98,0,0,388,389,5,108,0,0,389,390,5,101,0,0,390,82,1,
  	0,0,0,391,392,5,115,0,0,392,393,5,107,0,0,393,394,5,105,0,0,394,395,5,
  	112,0,0,395,84,1,0,0,0,396,397,5,112,0,0,397,398,5,117,0,0,398,399,5,
  	114,0,0,399,400,5,101,0,0,400,86,1,0,0,0,401,402,5,111,0,0,402,403,5,
  	118,0,0,403,404,5,101,0,0,404,405,5,114,0,0,405,406,5,114,0,0,406,407,
  	5,105,0,0,407,408,5,100,0,0,408,409,5,101,0,0,409,88,1,0,0,0,410,414,
  	3,91,45,0,411,414,3,93,46,0,412,414,3,95,47,0,413,410,1,0,0,0,413,411,
  	1,0,0,0,413,412,1,0,0,0,414,90,1,0,0,0,415,416,5,112,0,0,416,417,5,117,
  	0,0,417,418,5,98,0,0,418,419,5,108,0,0,419,420,5,105,0,0,420,421,5,99,
  	0,0,421,92,1,0,0,0,422,423,5,112,0,0,423,424,5,114,0,0,424,425,5,105,
  	0,0,425,426,5,118,0,0,426,427,5,97,0,0,427,428,5,116,0,0,428,429,5,101,
  	0,0,429,94,1,0,0,0,430,431,5,112,0,0,431,432,5,114,0,0,432,433,5,111,
  	0,0,433,434,5,116,0,0,434,435,5,101,0,0,435,436,5,99,0,0,436,437,5,116,
  	0,0,437,438,5,101,0,0,438,439,5,100,0,0,439,96,1,0,0,0,440,443,3,99,49,
  	0,441,443,3,117,58,0,442,440,1,0,0,0,442,441,1,0,0,0,443,98,1,0,0,0,444,
  	453,3,101,50,0,445,453,3,103,51,0,446,453,3,105,52,0,447,453,3,107,53,
  	0,448,453,3,109,54,0,449,453,3,111,55,0,450,453,3,113,56,0,451,453,3,
  	115,57,0,452,444,1,0,0,0,452,445,1,0,0,0,452,446,1,0,0,0,452,447,1,0,
  	0,0,452,448,1,0,0,0,452,449,1,0,0,0,452,450,1,0,0,0,452,451,1,0,0,0,453,
  	100,1,0,0,0,454,455,5,101,0,0,455,456,5,97,0,0,456,457,5,120,0,0,457,
  	102,1,0,0,0,458,459,5,101,0,0,459,460,5,98,0,0,460,461,5,120,0,0,461,
  	104,1,0,0,0,462,463,5,101,0,0,463,464,5,99,0,0,464,465,5,120,0,0,465,
  	106,1,0,0,0,466,467,5,101,0,0,467,468,5,100,0,0,468,469,5,120,0,0,469,
  	108,1,0,0,0,470,471,5,101,0,0,471,472,5,115,0,0,472,473,5,105,0,0,473,
  	110,1,0,0,0,474,475,5,101,0,0,475,476,5,100,0,0,476,477,5,105,0,0,477,
  	112,1,0,0,0,478,479,5,101,0,0,479,480,5,115,0,0,480,481,5,112,0,0,481,
  	114,1,0,0,0,482,483,5,101,0,0,483,484,5,98,0,0,484,485,5,112,0,0,485,
  	116,1,0,0,0,486,495,3,119,59,0,487,495,3,121,60,0,488,495,3,123,61,0,
  	489,495,3,125,62,0,490,495,3,127,63,0,491,495,3,129,64,0,492,495,3,131,
  	65,0,493,495,3,133,66,0,494,486,1,0,0,0,494,487,1,0,0,0,494,488,1,0,0,
  	0,494,489,1,0,0,0,494,490,1,0,0,0,494,491,1,0,0,0,494,492,1,0,0,0,494,
  	493,1,0,0,0,495,118,1,0,0,0,496,497,5,120,0,0,497,498,5,109,0,0,498,499,
  	5,109,0,0,499,500,5,48,0,0,500,120,1,0,0,0,501,502,5,120,0,0,502,503,
  	5,109,0,0,503,504,5,109,0,0,504,505,5,49,0,0,505,122,1,0,0,0,506,507,
  	5,120,0,0,507,508,5,109,0,0,508,509,5,109,0,0,509,510,5,50,0,0,510,124,
  	1,0,0,0,511,512,5,120,0,0,512,513,5,109,0,0,513,514,5,109,0,0,514,515,
  	5,51,0,0,515,126,1,0,0,0,516,517,5,120,0,0,517,518,5,109,0,0,518,519,
  	5,109,0,0,519,520,5,52,0,0,520,128,1,0,0,0,521,522,5,120,0,0,522,523,
  	5,109,0,0,523,524,5,109,0,0,524,525,5,53,0,0,525,130,1,0,0,0,526,527,
  	5,120,0,0,527,528,5,109,0,0,528,529,5,109,0,0,529,530,5,54,0,0,530,132,
  	1,0,0,0,531,532,5,120,0,0,532,533,5,109,0,0,533,534,5,109,0,0,534,535,
  	5,55,0,0,535,134,1,0,0,0,536,541,3,137,68,0,537,541,3,139,69,0,538,541,
  	3,141,70,0,539,541,3,143,71,0,540,536,1,0,0,0,540,537,1,0,0,0,540,538,
  	1,0,0,0,540,539,1,0,0,0,541,136,1,0,0,0,542,543,5,95,0,0,543,544,5,95,
  	0,0,544,545,5,115,0,0,545,546,5,116,0,0,546,547,5,100,0,0,547,548,5,99,
  	0,0,548,549,5,97,0,0,549,550,5,108,0,0,550,551,5,108,0,0,551,138,1,0,
  	0,0,552,553,5,95,0,0,553,554,5,95,0,0,554,555,5,99,0,0,555,556,5,100,
  	0,0,556,557,5,101,0,0,557,558,5,99,0,0,558,559,5,108,0,0,559,140,1,0,
  	0,0,560,561,5,95,0,0,561,562,5,95,0,0,562,563,5,102,0,0,563,564,5,97,
  	0,0,564,565,5,115,0,0,565,566,5,116,0,0,566,567,5,99,0,0,567,568,5,97,
  	0,0,568,569,5,108,0,0,569,570,5,108,0,0,570,142,1,0,0,0,571,572,5,95,
  	0,0,572,573,5,95,0,0,573,574,5,116,0,0,574,575,5,104,0,0,575,576,5,105,
  	0,0,576,577,5,115,0,0,577,578,5,99,0,0,578,579,5,97,0,0,579,580,5,108,
  	0,0,580,581,5,108,0,0,581,144,1,0,0,0,582,584,3,1,0,0,583,585,5,46,0,
  	0,584,583,1,0,0,0,584,585,1,0,0,0,585,587,1,0,0,0,586,588,7,0,0,0,587,
  	586,1,0,0,0,588,589,1,0,0,0,589,587,1,0,0,0,589,590,1,0,0,0,590,591,1,
  	0,0,0,591,592,3,1,0,0,592,593,3,3,1,0,593,146,1,0,0,0,594,596,3,1,0,0,
  	595,597,5,46,0,0,596,595,1,0,0,0,596,597,1,0,0,0,597,599,1,0,0,0,598,
  	600,7,1,0,0,599,598,1,0,0,0,600,601,1,0,0,0,601,599,1,0,0,0,601,602,1,
  	0,0,0,602,603,1,0,0,0,603,604,3,1,0,0,604,605,3,3,1,0,605,148,1,0,0,0,
  	606,607,5,111,0,0,607,608,5,112,0,0,608,609,5,101,0,0,609,610,5,114,0,
  	0,610,611,5,97,0,0,611,612,5,116,0,0,612,613,5,111,0,0,613,614,5,114,
  	0,0,614,150,1,0,0,0,615,617,7,2,0,0,616,618,5,61,0,0,617,616,1,0,0,0,
  	617,618,1,0,0,0,618,623,1,0,0,0,619,620,5,61,0,0,620,623,5,61,0,0,621,
  	623,5,61,0,0,622,615,1,0,0,0,622,619,1,0,0,0,622,621,1,0,0,0,623,152,
  	1,0,0,0,624,628,7,3,0,0,625,627,7,4,0,0,626,625,1,0,0,0,627,630,1,0,0,
  	0,628,626,1,0,0,0,628,629,1,0,0,0,629,154,1,0,0,0,630,628,1,0,0,0,631,
  	634,3,157,78,0,632,634,3,159,79,0,633,631,1,0,0,0,633,632,1,0,0,0,634,
  	156,1,0,0,0,635,636,5,48,0,0,636,637,5,120,0,0,637,639,1,0,0,0,638,640,
  	7,5,0,0,639,638,1,0,0,0,640,641,1,0,0,0,641,639,1,0,0,0,641,642,1,0,0,
  	0,642,158,1,0,0,0,643,645,7,6,0,0,644,643,1,0,0,0,645,646,1,0,0,0,646,
  	644,1,0,0,0,646,647,1,0,0,0,647,160,1,0,0,0,648,649,5,123,0,0,649,650,
  	5,123,0,0,650,654,1,0,0,0,651,653,9,0,0,0,652,651,1,0,0,0,653,656,1,0,
  	0,0,654,655,1,0,0,0,654,652,1,0,0,0,655,657,1,0,0,0,656,654,1,0,0,0,657,
  	658,5,125,0,0,658,659,5,125,0,0,659,162,1,0,0,0,660,662,7,7,0,0,661,660,
  	1,0,0,0,662,663,1,0,0,0,663,661,1,0,0,0,663,664,1,0,0,0,664,665,1,0,0,
  	0,665,666,6,81,0,0,666,164,1,0,0,0,667,669,5,13,0,0,668,670,5,10,0,0,
  	669,668,1,0,0,0,669,670,1,0,0,0,670,673,1,0,0,0,671,673,5,10,0,0,672,
  	667,1,0,0,0,672,671,1,0,0,0,673,674,1,0,0,0,674,675,6,82,0,0,675,166,
  	1,0,0,0,676,677,5,47,0,0,677,678,5,42,0,0,678,682,1,0,0,0,679,681,9,0,
  	0,0,680,679,1,0,0,0,681,684,1,0,0,0,682,683,1,0,0,0,682,680,1,0,0,0,683,
  	685,1,0,0,0,684,682,1,0,0,0,685,686,5,42,0,0,686,687,5,47,0,0,687,688,
  	1,0,0,0,688,689,6,83,0,0,689,168,1,0,0,0,690,691,5,47,0,0,691,692,5,47,
  	0,0,692,696,1,0,0,0,693,695,8,8,0,0,694,693,1,0,0,0,695,698,1,0,0,0,696,
  	694,1,0,0,0,696,697,1,0,0,0,697,699,1,0,0,0,698,696,1,0,0,0,699,700,6,
  	84,0,0,700,170,1,0,0,0,701,702,9,0,0,0,702,172,1,0,0,0,23,0,183,413,442,
  	452,494,540,584,589,596,601,617,622,628,633,641,646,654,663,669,672,682,
  	696,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  zhllexerLexerStaticData = staticData.release();
}

}

ZHLLexer::ZHLLexer(CharStream *input) : Lexer(input) {
  ZHLLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *zhllexerLexerStaticData->atn, zhllexerLexerStaticData->decisionToDFA, zhllexerLexerStaticData->sharedContextCache);
}

ZHLLexer::~ZHLLexer() {
  delete _interpreter;
}

std::string ZHLLexer::getGrammarFileName() const {
  return "ZHLLexer.g4";
}

const std::vector<std::string>& ZHLLexer::getRuleNames() const {
  return zhllexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& ZHLLexer::getChannelNames() const {
  return zhllexerLexerStaticData->channelNames;
}

const std::vector<std::string>& ZHLLexer::getModeNames() const {
  return zhllexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& ZHLLexer::getVocabulary() const {
  return zhllexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ZHLLexer::getSerializedATN() const {
  return zhllexerLexerStaticData->serializedATN;
}

const atn::ATN& ZHLLexer::getATN() const {
  return *zhllexerLexerStaticData->atn;
}




void ZHLLexer::initialize() {
  ::antlr4::internal::call_once(zhllexerLexerOnceFlag, zhllexerLexerInitialize);
}
