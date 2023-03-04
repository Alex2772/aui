//
// Created by alex2 on 6/12/2021.
//

#pragma once

#include <AUI/Common/AString.h>
#include "IToken.h"

#ifdef CONST
#undef CONST
#undef TRUE
#undef FALSE
#undef DELETE
#undef THIS
#endif

class KeywordToken: public IToken {
public:
    enum Type {
        NONE,

        AUTO,
        BREAK,
        CASE,
        CONST,
        CONTINUE,
        DEFAULT,
        DO,
        ELSE,
        ENUM,
        EXTERN,
        FOR,
        GOTO,
        IF,
        RETURN,
        SIGNED,
        SIZEOF,
        STATIC,
        STRUCT,
        SWITCH,
        TYPEDEF,
        UNION,
        UNSIGNED,
        VOLATILE,
        WHILE,

        ASM,
        CONST_CAST,
        EXPORT,
        MUTABLE,
        PRIVATE,
        STATIC_CAST,
        TRUE,
        USING,
        DELETE,
        FALSE,
        NAMESPACE,
        PROTECTED,
        TEMPLATE,
        TRY,
        VIRTUAL,
        CATCH,
        DYNAMIC_CAST,
        FRIEND,
        NEW,
        PUBLIC,
        THIS,
        TYPEID,
        CLASS,
        EXPLICIT,
        INLINE,
        OPERATOR,
        REINTERPRET_CAST,
        THROW,
        TYPENAME,
        NULLPTR
    };

private:
    Type mType;

public:
    KeywordToken(Type type) : mType(type) {}

    const char* getName() override;

    [[nodiscard]]
    Type getType() const {
        return mType;
    }

    static Type fromName(const AString& name);
};


