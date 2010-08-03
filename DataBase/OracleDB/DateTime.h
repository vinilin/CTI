// DateTime.h: interface for the DateTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATETIME_H__4823DE7C_8C34_43B2_97EF_7744EA0A04FD__INCLUDED_)
#define AFX_DATETIME_H__4823DE7C_8C34_43B2_97EF_7744EA0A04FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786)
namespace CTI 
{
    namespace Oracle
    {
        enum MonthsEnum
        {
            jan = 1,
            feb,
            mar,
            apr,
            may,
            jun,
            jul,
            aug,
            sep,
            oct,
            nov,
            dec
        };
        // helper date/time class with no input validation at all
        class DateTime
        {
        private:
        sb2 y;
        MonthsEnum m;
        ub1 d;
        ub1 h;
        ub1 i;
        ub1 s;

        public:

        inline DateTime (void) 
        {
        };

        inline DateTime ( ub1 dd, MonthsEnum mm,
                            ub2 yyyy, ub1 hh = 0,
                            ub1 mi = 0, ub1 ss = 0) 
                        : y (yyyy), m (mm), d (dd), h (hh), i (mi), s (ss)
                { 
                };

                inline DateTime (
                        IN const OCIDate& o)
                        { operator = (o); };

        public:
            inline ub1 day (void) const 
            { 
                return d; 
            };
            inline void day (ub1 dd)
            { 
                d = dd; 
            };

            inline MonthsEnum mon () const
            { 
                return m; 
            };
            inline void mon (MonthsEnum mm)
            { 
                m = mm; 
            };
            inline sb2 year () const
            { 
                return y; 
            };
            inline void year (sb2 yy)
            { 
                y = yy; 
            };
            inline ub1 hour () const
            { 
                return (h); 
            };
            inline void hour (ub1 hh)
            { 
                h = hh; 
            };
            inline ub1 minute () const
            { 
                return i; 
            };
            inline void minute (ub1 mi)
            { 
                i = mi; 
            };
            inline ub1 sec () const
            { 
                return s; 
            };
            inline void sec (ub1 ss)
            { 
                s = ss;
            };
            inline DateTime& operator = (const OCIDate& o)
            {
                y = o.OCIDateYYYY;
                m = (MonthsEnum) (o.OCIDateMM);
                d = o.OCIDateDD;
                h = o.OCIDateTime.OCITimeHH;
                i = o.OCIDateTime.OCITimeMI;
                s = o.OCIDateTime.OCITimeSS;
                return *this;
            };
            inline void set (OCIDate& o) const
            {
                o.OCIDateYYYY = y;
                o.OCIDateMM = static_cast <ub1> (m);
                o.OCIDateDD = d;
                o.OCIDateTime.OCITimeHH = h;
                o.OCIDateTime.OCITimeMI = i;
                o.OCIDateTime.OCITimeSS = s;
            };
        }; // DateTime class
    }
}; // oralib namespace

#endif // !defined(AFX_DATETIME_H__4823DE7C_8C34_43B2_97EF_7744EA0A04FD__INCLUDED_)
