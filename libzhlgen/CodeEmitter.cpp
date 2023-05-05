#include "CodeEmitter.h"

CodeEmitter::TypeEmitter::TypeEmitter(CodeEmitter* emitter) : _emitter(emitter) {

}

template<typename T>
void CodeEmitter::TypeEmitter::operator()(T const& t) {
    _emitter->EmitType(t);
}

CodeEmitter::CodeEmitter() : _decls("IsaacRepentance.h"), _impl("IsaacRepentance.cpp") {

}

void CodeEmitter::ProcessZHLFiles(fs::path const& base) {
	for (fs::directory_entry const& entry : fs::directory_iterator(base)) {
		//std::cout << "File " << entry.path() << std::endl;
		if (!entry.is_regular_file())
			continue;

		//std::cout << "Ext " << entry.path().extension() << std::endl;
		if (entry.path().extension() != std::string(".zhl"))
			continue;

		ProcessFile(entry.path());
	}
}

void CodeEmitter::ProcessFile(fs::path const& file) {
    std::ifstream stream(file);

    if (!stream.is_open()) {
        return;
    }

    // std::cout << "Visiting " << path << std::endl;
    antlr4::ANTLRInputStream input_stream(stream);
    ZHLLexer lexer(&input_stream);
    antlr4::CommonTokenStream tokens(&lexer);
    ZHLParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.zhl();

    if (lexer.getNumberOfSyntaxErrors() != 0 || parser.getNumberOfSyntaxErrors() != 0) {
        std::cerr << "Error while parsing " << file << std::endl;
        throw std::runtime_error("Parse error");
    }
    Parser p2(&_global, &_types);
    p2.visit(tree);
}

void CodeEmitter::Emit() {
    CheckDependencies();
    CheckVTables();

    for (auto const& [_, type] : _types) {
        if (type.IsStruct()) {
            Emit(type.GetStruct());
        }
    }
}

void CodeEmitter::Emit(Type const& type) {
    if (type._synonym) {
        Emit(*type._synonym);
        return;
    }

    if (type._base) {
        Emit(*type._base);
        if (type._const) {
            Emit(" const");
        }
        else if (type.IsPointer()) {
            Emit(type._pointerDecl.front());
        }
    }
    else {
        std::visit(TypeEmitter(this), type._value);
    }
}

void CodeEmitter::Emit(Struct const& s) {
    if (InProcessing(s) || Emitted(s)) {
        return;
    }

    _processingStructures.insert(s._name);

    EmitDependencies(s);
    EmitDecl();
    EmitTab();
    Emit("struct ");
    Emit(s._name);
    if (!s._parents.empty()) {
        Emit(" : ");
        for (int i = 0; i < s._parents.size(); ++i) { 
            Emit(VisibilityToString(std::get<Visibility>(s._parents[i])));
            Emit(" ");
            Emit(std::get<Type*>(s._parents[i])->GetStruct()._name);
            if (i != s._parents.size() - 1) {
                Emit(", ");
            }
        }
    }
    Emit(" {");
    EmitNL();
    IncrDepth();

    for (Variable const& var : s._namespace._fields) {
        Emit(var);
    }

    for (Signature const& sig : s._namespace._signatures) {
        Emit(sig, false);
    }

    for (Signature const& sig : s._overridenVirtualFunctions) {
        Emit(sig, true);
    }

    for (std::variant<Signature, Skip> const& sig : s._virtualFunctions) {
        Emit(sig);
    }

    for (GenericCode const& code : s._namespace._generic) {
        Emit(code);
        EmitNL();
    }

    DecrDepth();
    Emit("};");
    EmitNL();
    EmitNL();

    _processingStructures.erase(s._name);
    _emittedStructures.insert(s._name);
}

void CodeEmitter::Dump() {
    std::set<std::string> pending;
    for (auto const& [name, type] : _types) {
        std::cout << name << " => " << type.ToString(true) << std::endl;

        if (!type.IsResolved()) {
            if (type.IsEmpty()) {
                std::cout << "EMPTY TYPE" << std::endl;
            }
            else {
                pending.insert(std::get<std::string>(type._value));
            }
        }
    }

    std::cout << "UNRESOLVED TYPES:" << std::endl;
    for (std::string const& s : pending) {
        std::cout << s << std::endl;
    }
}

void CodeEmitter::EmitType(BasicType const& t) {
    if (t._sign) {
        Emit(SignednessToString(*t._sign));
        Emit(" ");
    }

    if (t._length) {
        Emit(LengthToString(*t._length));
        Emit(" ");
    }

    Emit(BasicTypeToString(t._type));
}

void CodeEmitter::EmitType(Struct const& s) {
    Emit(s._name);
}

void CodeEmitter::EmitType(FunctionPtr* ptr) {
    if (_variableContext) {
        Emit(*ptr->_ret);
        Emit(" (");

        if (ptr->_convention) {
            Emit("");
        }

        if (ptr->_scope) {
            Emit(*ptr->_scope);
            Emit("::");
        }

        Emit("*");
        Emit(_variableContext->_name);
        Emit(")(");

        for (int i = 0; i < ptr->_parameters.size(); ++i) {
            Emit(*(ptr->_parameters[i]));
            if (i != ptr->_parameters.size()) {
                Emit(", ");
            }
        }

        Emit(")");
    }
}

void CodeEmitter::EmitType(std::string const& t) {
    Emit(t);
}

void CodeEmitter::EmitType(EmptyType const&) {
    throw std::runtime_error("[FATAL] Attempting to emit empty type");
}

void CodeEmitter::EmitTab() {
    for (int i = 0; i < _emitDepth; ++i) {
        *_emitContext << "\t";
    }
}

void CodeEmitter::Emit(std::string const& s) {
    *_emitContext << s;
}

void CodeEmitter::EmitNL() {
    *_emitContext << std::endl;
}

void CodeEmitter::EmitDecl() {
    _emitContext = &_decls;
}

void CodeEmitter::EmitImpl() {
    _emitContext = &_impl;
}

void CodeEmitter::IncrDepth() {
    ++_emitDepth;
}

void CodeEmitter::DecrDepth() {
    --_emitDepth;
}

void CodeEmitter::EmitDependencies(Struct const& s) {
    for (Type* dep : s._deps) {
        if (dep->IsStruct()) {
            Emit(std::get<Struct>(dep->_value));
        }
        else {
            std::ostringstream str;
            str << "[ERROR] Structure " << s._name << " specifies unresolved dependency " << dep->_name << std::endl;
            throw std::runtime_error(str.str());
        }
    }

    for (auto const& [dep, vis] : s._parents) {
        if (dep->IsStruct()) {
            Emit(dep->GetStruct());
        }
        else {
            std::ostringstream str;
            str << "[ERROR] Structure " << s._name << " specified unresolved parent " << dep->_name << std::endl;
            throw std::runtime_error(str.str());
        }
    }
}

bool CodeEmitter::Emitted(Struct const& s) const {
    return _emittedStructures.find(s._name) != _emittedStructures.end();
}

void CodeEmitter::AssertEmitted(Struct const& s) {
    if (!Emitted(s)) {
        std::ostringstream str;
        str << "[FATAL] Structure " << _currentStructure->_name << " has not specified direct dependency on structure " << s._name << std::endl;
        throw std::runtime_error(str.str());
    }
}

bool CodeEmitter::InProcessing(Struct const& s) const {
    return _processingStructures.find(s._name) != _processingStructures.end();
}

void CodeEmitter::AssertReady(Type const* t) {
    if (t->_pending && t->_name != "std") {
        std::ostringstream str;
        str << "[FATAL] Structure " << std::get<Struct>(t->_value)._name << " has not been properly defined" << std::endl;
        throw std::runtime_error(str.str());
    }
}

void CodeEmitter::CheckVTables() {
    for (auto const& [_, type] : _types) {
        if (!type.IsStruct()) {
            continue;
        }

        Struct const& s = type.GetStruct();
        CheckVTableInternalConsistency(s);
        
        std::set<std::string> seen;
        std::vector<Struct const*> parents;
        std::stack<Struct const*> parentsBuffer;

        for (auto const& [parent, _] : s._parents) {
            Struct const& parentStruct = parent->GetStruct();
            if (seen.find(parentStruct._name) != seen.end()) {
                continue;
            }

            parentsBuffer.push(&parentStruct);
            seen.insert(parentStruct._name);
            // CheckVTableHierarchyConsistency(s, parent->GetStruct());
        }

        while (!parentsBuffer.empty()) {
            Struct const* parent = parentsBuffer.top();
            parentsBuffer.pop();

            for (auto const& [parentParent, _] : parent->_parents) {
                Struct const& parentStruct = parentParent->GetStruct();
                if (seen.find(parentStruct._name) != seen.end()) {
                    continue;
                }

                parentsBuffer.push(&parentStruct);
            }

            parents.push_back(parent);
        }

        CheckVTableHierarchyConsistency(s, parents);
    }
}

void CodeEmitter::CheckVTableInternalConsistency(Struct const& s) {
    // Check that each function declared as override does not conflict with 
    // a function not declared as override.

    for (Signature const& sig : s._overridenVirtualFunctions) {
        for (std::variant<Signature, Skip> const& fn : s._virtualFunctions) {
            if (std::holds_alternative<Signature>(fn)) {
                Signature const& other = std::get<Signature>(fn);
                if (other._function._name == sig._function._name) {
                    if (other._function == sig._function) {
                        std::ostringstream str;
                        str << "[FATAL] In structure " << s._name << ", virtual function " << sig._function._name << " overrides itself" << std::endl;
                        throw std::runtime_error(str.str());
                    }
                }
            }
        }
    }
}

void CodeEmitter::CheckVTableHierarchyConsistency(Struct const& s, std::vector<Struct const*> const& parents) {
    // Check that each function declared as override has an actual non overidden
    // version somewhere.

    for (Signature const& sig : s._overridenVirtualFunctions) {
        bool found = false;
        for (Struct const* parent : parents) {
            for (std::variant<Signature, Skip> const& fn : parent->_virtualFunctions) {
                if (std::holds_alternative<Signature>(fn)) {
                    Signature const& other = std::get<Signature>(fn);
                    if (other._function._name == sig._function._name) {
                        if (other._function == sig._function) {
                            found = true;
                            break;
                        }
                    }
                }
            }

            if (found) {
                break;
            }
        }

        if (!found) {
            std::ostringstream str;
            str << "Structure " << s._name << " specified function " << sig._function._name << " as an override, but it doesn't override anything" << std::endl;
            throw std::runtime_error(str.str());
        }
    }

    // Check that each function declared as not override is not actually an override.
    for (std::variant<Signature, Skip> const& fun : s._virtualFunctions) {
        if (std::holds_alternative<Skip>(fun)) {
            continue;
        }

        Signature const& currentFun = std::get<Signature>(fun);
        std::optional<std::string> badOverride;

        for (Struct const* parent : parents) {
            for (std::variant<Signature, Skip> const& other : parent->_virtualFunctions) {
                if (std::holds_alternative<Signature>(other)) {
                    Signature const& otherFun = std::get<Signature>(other);
                    if (currentFun._function == otherFun._function) {
                        badOverride = parent->_name;
                        break;
                    }
                }
            }

            if (badOverride) {
                std::ostringstream str;
                str << "Structure " << s._name << " specified function " << currentFun._function._name <<
                    " as a non override, but it overrides its parent in class " << *badOverride << std::endl;
                throw std::runtime_error(str.str());
            }
        }
    }
}

void CodeEmitter::CheckDependencies() {
    for (auto const& [_, type] : _types) {
        if (!type.IsStruct()) {
            continue;
        }

        CheckDependencies(type);
    }
}

void CodeEmitter::CheckDependencies(Type const& t) {
    Struct const& s = t.GetStruct();

    // Assert dependencies have a definition
    for (Type* t: s._deps) {
        AssertReady(t);
    }

    // Assert parents have a definition
    for (auto const& [type, _] : s._parents) {
        AssertReady(type);
    }

    // Check fields
    for (Variable const& v : s._namespace._fields) {
        if (v._type->IsStruct() && !v._type->IsPointer()) {
            AssertReady(v._type);

            Struct const& var = v._type->GetStruct();

            bool found = false;
            for (Type* t : s._deps) {
                Struct const& dep = t->GetStruct();
                if (dep._name == var._name) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::stack<Type*> parents;
                for (auto const& [type, _] : s._parents) {
                    parents.push(type);
                }

                while (!parents.empty()) {
                    Type* t = parents.top();
                    parents.pop();

                    if (t->GetStruct()._name == var._name) {
                        found = true;
                        break;
                    }

                    for (auto const& [type, _] : t->GetStruct()._parents) {
                        parents.push(type);
                    }
                }
            }

            if (!found) {
                _logger << ErrorLogger::warn << " Structure " << s._name << "'s field " << v._name << " has non pointer structure type " << v._type->GetStruct()._name << 
                    " which is not specified in the dependency list, this may lead to compile errors" << ErrorLogger::endl << ErrorLogger::_end;
            }
        }
    }
}

void CodeEmitter::Emit(Variable const& var) {
    _variableContext = &var;

    EmitTab();
    Emit(*var._type);
    Emit(" ");

    if (!std::holds_alternative<FunctionPtr*>(var._type->_value)) {
        Emit(var._name);
    }

    if (var._type->IsArray()) {
        Emit("[");
        Emit(std::to_string(var._type->_arraySize));
        Emit("]");
    }

    Emit(";");
    EmitNL();

    _variableContext = nullptr;

    void (CodeEmitter:: * foo[10])();
}

void CodeEmitter::Emit(Signature const& var, bool isVirtual) {
    EmitTab();
    Function const& fun = var._function;
    Emit("LIBZHL_API ");
    if (isVirtual) {
        Emit("virtual ");
    }
    Emit(fun);
    EmitNL();
}

void CodeEmitter::Emit(Function const& fun) {
    uint32_t qualifiers = fun._qualifiers;
    if (qualifiers & STATIC) {
        Emit("static ");
    }

    Emit(*fun._ret);
    Emit(" ");

    if (fun._convention) {
        if (*fun._convention == THISCALL && _currentStructure) {
            // Nop
        }
        else {
            Emit(CallingConventionToString(*fun._convention));
            Emit(" ");
        }
    }

    Emit(fun._name);
    Emit("(");
    for (int i = 0; i < fun._params.size(); ++i) {
        Emit(*(fun._params[i]._type));
        Emit(" ");
        Emit(fun._params[i]._name);
        if (i != fun._params.size() - 1) {
            Emit(", ");
        }
    }
    Emit(");");
}

void CodeEmitter::Emit(std::variant<Signature, Skip> const& sig) {
    if (std::holds_alternative<Skip>(sig)) {
        Emit("virtual void unk");
        Emit(std::to_string(_virtualFnUnk));
        Emit("() { }");
        ++_virtualFnUnk;
    }
    else {
        Emit(std::get<Signature>(sig), true);
    }
}

void CodeEmitter::Emit(PointerDecl const& ptr) {
    switch (ptr._kind) {
    case LREF:
        Emit(" &");
        break;

    case RREF:
        Emit(" &&");
        break;

    case POINTER:
        Emit(" *");
        break;
    }

    if (ptr._const) {
        Emit(" const");
    }
}