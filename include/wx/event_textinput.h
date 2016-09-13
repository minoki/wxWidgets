
#ifndef _WX_EVENT_TEXTINPUT_H_
#define _WX_EVENT_TEXTINPUT_H_

#include "wx/event.h"
#include "wx/attrstr.h"

class WXDLLIMPEXP_CORE wxTextInputRange
{
public:
    wxTextInputRange() : m_location((unsigned int)(-1)), m_length((unsigned int)(-1)) {}
    wxTextInputRange(unsigned int loc, unsigned int len)
       : m_location(loc), m_length(len) {}

    unsigned int GetLocation() const { return m_location; }
    unsigned int GetLength() const { return m_length; }

public:
    unsigned int m_location;
    unsigned int m_length;
};

class WXDLLIMPEXP_FWD_CORE wxTextInputEvent;
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_CORE, wxEVT_TEXT_INPUT, wxTextInputEvent);
#if defined(__WXMAC__)
class WXDLLIMPEXP_FWD_CORE wxOSXDoCommandBySelectorEvent;
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_CORE, wxEVT_OSX_DO_COMMAND_BY_SELECTOR, wxOSXDoCommandBySelectorEvent);
#endif

// Text input event class

enum wxTextInputEventType
{
    WXTI_TYPE_PREEDIT_CHANGED, // attrString, range1 (, range2) ->
    WXTI_TYPE_PREEDIT_CLEAR, // ->
    WXTI_TYPE_PREEDIT_COMMITTED, // (attr?)string (, range1)->
    WXTI_TYPE_QUERY_HASPREEDIT, // -> bool
    WXTI_TYPE_QUERY_PREEDIT_RANGE, // -> range
    WXTI_TYPE_QUERY_SELECTED_RANGE, // -> range
    WXTI_TYPE_QUERY_SUBSTRING_FROM_RANGE, // range1 (-> attrString, range)
    WXTI_TYPE_QUERY_CHARINDEX_FOR_POINT, // point -> ulong
    WXTI_TYPE_QUERY_FIRSTRECT_FOR_CHARRANGE, // range1 -> rect (, range)
    WXTI_TYPE_INVALID
};
class WXDLLIMPEXP_CORE wxTextInputEvent : public wxEvent
{
public:
    wxTextInputEvent();

    wxTextInputEventType GetTextInputEventType() const;

    wxAttributedString GetCompositionString() const { return m_compositionString; }
    void SetCompositionString(wxAttributedString const& value) { m_compositionString = value; }

    wxRect GetRect() const { return m_rectParam; }
    void SetRect(wxRect value) { m_rectParam = value; }

    wxPoint GetPoint() const { return m_pointParam; }
    void SetPoint(wxPoint value) { m_pointParam = value; }

    wxTextInputRange GetRange1() const { return m_rangeParam1; }
    void SetRange1(wxTextInputRange value) { m_rangeParam1 = value; }

    wxTextInputRange GetRange2() const { return m_rangeParam2; }
    void SetRange2(wxTextInputRange value) { m_rangeParam2 = value; }

    bool GetBooleanResult() const { return m_booleanResult; }
    void SetBooleanResult(bool value) { m_booleanResult = value; }

    wxTextInputRange GetRangeResult() const { return m_rangeResult; }
    void SetRangeResult(wxTextInputRange value) { m_rangeResult = value; }

    wxRect GetRectResult() const { return m_rectResult; }
    void SetRectResult(wxRect value) { m_rectResult = value; }

    unsigned long GetULongResult() const { return m_ulongResult; }
    void SetULongResult(unsigned long value) { m_ulongResult = value; }

    wxString GetStringResult() const { return m_stringResult; }
    void SetStringResult(wxString const& str) { m_stringResult = str; }

    virtual wxEvent *Clone() const { return new wxTextInputEvent(*this); }

public:
    wxTextInputEventType m_textInputEventType;
    wxAttributedString m_compositionString;
    wxRect m_rectParam;
    wxPoint m_pointParam;
    wxTextInputRange m_rangeParam1;
    wxTextInputRange m_rangeParam2;
    bool m_booleanResult;
    wxTextInputRange m_rangeResult;
    wxRect m_rectResult;
    unsigned long m_ulongResult;
    wxString m_stringResult;

private:
    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxTextInputEvent)
};

inline wxTextInputEvent::wxTextInputEvent()
   : m_textInputEventType(WXTI_TYPE_INVALID),
     m_booleanResult(false),
     m_ulongResult(0)
{
    SetEventType(wxEVT_TEXT_INPUT);
}

inline wxTextInputEventType wxTextInputEvent::GetTextInputEventType() const
{
    return m_textInputEventType;
}


typedef void (wxEvtHandler::*wxTextInputEventFunction)(wxTextInputEvent&);
#define wxTextInputEventHandler(func) \
            wxEVENT_HANDLER_CAST(wxTextInputEventFunction, func)
#define EVT_TEXT_INPUT(func)  wx__DECLARE_EVT0(wxEVT_TEXT_INPUT, wxTextInputEventHandler(func))

#if defined(__WXMAC__)
class WXDLLIMPEXP_CORE wxOSXDoCommandBySelectorEvent : public wxEvent
{
public:
    wxOSXDoCommandBySelectorEvent();

    void SetSelector(void *selector);
    void *GetSelector() const;
    const char *GetSelectorCString() const;

    virtual wxEvent *Clone() const;

protected:
    void *m_selector;

private:
    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxOSXDoCommandBySelectorEvent)
};

typedef void (wxEvtHandler::*wxOSXDoCommandBySelectorEventFunction)(wxOSXDoCommandBySelectorEvent&);
#define wxOSXDoCommandBySelectorEventHandler(func) \
            wxEVENT_HANDLER_CAST(wxOSXDoCommandBySelectorEventFunction, func)
#define EVT_OSX_DO_COMMAND_BY_SELECTOR(func)  wx__DECLARE_EVT0(wxEVT_OSX_DO_COMMAND_BY_SELECTOR, wxOSXDoCommandBySelectorEventHandler(func))
#endif

#endif

