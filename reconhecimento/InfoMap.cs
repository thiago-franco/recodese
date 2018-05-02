using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SocialStoryteller
{
    public class ActionInfoMap
    {
        public String word;
        public String action;

        public ActionInfoMap(String w, String a)
        {
            word = w;
            action = a;
        }
    }

    public class CharacterInfoMap
    {
        public String word;
        public String character;

        public CharacterInfoMap(String w, String c)
        {
            word = w;
            character = c;
        }
    }

    public class PlaceInfoMap
    {
        public String word;
        public String place;

        public PlaceInfoMap(String w, String p)
        {
            word = w;
            place = p;
        }
    }
}
