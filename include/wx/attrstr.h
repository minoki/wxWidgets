
#ifndef _WX_ATTRSTR_H_
#define _WX_ATTRSTR_H_

#include "wx/utils.h"
#include "wx/string.h"
#include "wx/textctrl.h" // wxTextAttr

#include <vector> // std::vector
#include <utility> // std::pair

enum wxTextAttr2Flags
{
    wxTEXT_ATTR2_UNDERLINE_COLOUR = 0x00000001,
    wxTEXT_ATTR2_UNDERLINE_STYLE  = 0x00000002
};

class WXDLLIMPEXP_CORE wxTextAttr2 : public wxTextAttr
{
public:
    wxTextAttr2(const wxTextAttr& attr) : wxTextAttr(attr), m_flags2() { }
    wxTextAttr2(const wxTextAttr2& attr) : wxTextAttr(attr), m_flags2(attr.m_flags2), m_colUnderline(attr.m_colUnderline), m_underlineStyle(attr.m_underlineStyle) { }
    wxTextAttr2() : wxTextAttr(), m_flags2() {}
    void operator=(const wxTextAttr2& attr)
    {
        wxTextAttr::Copy(attr);
        m_flags2 = attr.m_flags2;
        m_colUnderline = attr.m_colUnderline;
    }
    void operator=(const wxTextAttr& attr)
    {
        wxTextAttr::Copy(attr);
        m_flags2 = 0;
    }

public:
    int m_flags2;
    wxColour m_colUnderline;
    enum UnderlineStyle {
        Underline_Normal,
        Underline_Thick,
        Underline_Wavy
    } m_underlineStyle;

public:
    void SetUnderlineColour(const wxColour& colUnderline)
    {
        m_colUnderline = colUnderline;
        m_flags2 |= wxTEXT_ATTR2_UNDERLINE_COLOUR;
    }
    void SetUnderlineStyle(wxTextAttr2::UnderlineStyle style)
    {
        m_underlineStyle = style;
        wxTextAttr::SetFontUnderlined(true);
        m_flags2 |= wxTEXT_ATTR2_UNDERLINE_STYLE;
    }
};

typedef std::pair<wxString,wxTextAttr2> wxAttributedStringSegment;

class WXDLLIMPEXP_CORE wxAttributedString
{
public:
    wxAttributedString();
    wxAttributedString(wxString string);
    wxAttributedString(std::vector<wxAttributedStringSegment> segments);
    wxString GetString() const;
    std::vector<wxAttributedStringSegment> GetSegments() const;

public:
    std::vector<wxAttributedStringSegment> m_segments;
};

#endif
