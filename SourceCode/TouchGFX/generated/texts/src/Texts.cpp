/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

//Default typed text database
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x6c, 0x69, 0x67, 0x68, 0x74, 0x20, 0x69, 0x6e, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x74, 0x79, 0x3a, 0x20, 0x2, 0x0, // @0 "light intensity: <>"
    0x54, 0x65, 0x6d, 0x70, 0x65, 0x72, 0x61, 0x74, 0x75, 0x72, 0x65, 0x3a, 0x20, 0x2, 0x0, // @19 "Temperature: <>"
    0x48, 0x75, 0x6d, 0x69, 0x64, 0x69, 0x74, 0x79, 0x3a, 0x2, 0x20, 0x25, 0x0, // @34 "Humidity:<> %"
    0x41, 0x69, 0x72, 0x20, 0x43, 0x6f, 0x6e, 0x64, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x65, 0x72, 0x0, // @47 "Air Conditioner"
    0x54, 0x65, 0x6d, 0x70, 0x3a, 0x20, 0x2, 0x0, // @63 "Temp: <>"
    0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x20, 0x30, 0x0, // @71 "Device 0"
    0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x20, 0x31, 0x0, // @80 "Device 1"
    0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x20, 0x32, 0x0, // @89 "Device 2"
    0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x20, 0x33, 0x0, // @98 "Device 3"
    0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x20, 0x34, 0x0, // @107 "Device 4"
    0x4c, 0x69, 0x67, 0x68, 0x74, 0x20, 0x34, 0xa, 0x0, // @116 "Light 4?"
    0x4c, 0x69, 0x67, 0x68, 0x74, 0x20, 0x30, 0x0, // @125 "Light 0"
    0x4c, 0x69, 0x67, 0x68, 0x74, 0x20, 0x31, 0x0, // @133 "Light 1"
    0x4c, 0x69, 0x67, 0x68, 0x74, 0x20, 0x32, 0x0, // @141 "Light 2"
    0x4c, 0x69, 0x67, 0x68, 0x74, 0x20, 0x33, 0x0, // @149 "Light 3"
    0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x0, // @157 "Service"
    0x53, 0x65, 0x74, 0x74, 0x69, 0x6e, 0x67, 0x0, // @165 "Setting"
    0x4c, 0x69, 0x67, 0x68, 0x74, 0x0, // @173 "Light"
    0x42, 0x41, 0x43, 0x4b, 0x0, // @179 "BACK"
    0x44, 0x4f, 0x57, 0x4e, 0x0, // @184 "DOWN"
    0x48, 0x49, 0x47, 0x48, 0x0, // @189 "HIGH"
    0x32, 0x35, 0x30, 0x0, // @194 "250"
    0x48, 0x72, 0x73, 0x0, // @198 "Hrs"
    0x4c, 0x4f, 0x57, 0x0, // @202 "LOW"
    0x4d, 0x45, 0x44, 0x0, // @206 "MED"
    0x4d, 0x69, 0x6e, 0x0, // @210 "Min"
    0x53, 0x65, 0x63, 0x0, // @214 "Sec"
    0x32, 0x32, 0x0, // @218 "22"
    0x55, 0x50, 0x0 // @221 "UP"
};
TEXT_LOCATION_FLASH_PRAGMA
KEEP extern uint32_t const indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

//array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

//Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}
