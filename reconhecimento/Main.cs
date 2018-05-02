using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using mshtml;
using System.Text;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Net;

namespace SocialStoryteller
{    
    public partial class Main : System.Windows.Forms.Form
    {
        public enum State {None, Login, OK, Erro};

        public State state;
        public WebBrowser web;
        public string postID;
        public List<String> currentActions;
        public List<ActionInfoMap> validActions;
        public List<CharacterInfoMap> validCharacters;
        public List<PlaceInfoMap> validPlaces;
        private TcpListener tcpListener;
        private Thread listenThread;

        public Main()
        {
            InitializeComponent();
            state = State.None;
            postID = "";

            currentActions = new List<String>();
            validActions = new List<ActionInfoMap>();
            validCharacters = new List<CharacterInfoMap>();
            validPlaces = new List<PlaceInfoMap>();

            validActions.Clear();
            validCharacters.Clear();
            validPlaces.Clear();
            currentActions.Clear();

            InitCharacters();
            InitPlaces();
            InitActions();

            this.tcpListener = new TcpListener(IPAddress.Any, 4040);
            this.listenThread = new Thread(new ThreadStart(ListenForClients));
            this.listenThread.Start();

        }
        

        private void ListenForClients()
        {
            this.tcpListener.Start();

            while (true)
            {
                //blocks until a client has connected to the server
                TcpClient client = this.tcpListener.AcceptTcpClient();

                //create a thread to handle communication
                //with connected client
                Thread clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));
                clientThread.Start(client);
                
            }
        }

        private void HandleClientComm(object client)
        {
            TcpClient tcpClient = (TcpClient)client;
            NetworkStream clientStream = tcpClient.GetStream();

            byte[] message = new byte[4096];
            int bytesRead;

            while (true)
            {
                bytesRead = 0;

                try
                {
                    bytesRead = clientStream.Read(message, 0, 4096);
                }
                catch
                {
                    break;
                }

                if (bytesRead == 0)
                {
                    break;
                }

                ASCIIEncoding encoder = new ASCIIEncoding();

                if (encoder.GetString(message, 0, bytesRead).Equals("NewEvents"))
                    currentActions.Clear();
                else
                    currentActions.Add(encoder.GetString(message, 0, bytesRead));
            }

            tcpClient.Close();
        }


        private void button5_Click(object sender, EventArgs e)
        {
            TcpClient client = new TcpClient();

            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5555);

            client.Connect(serverEndPoint);

            NetworkStream clientStream = client.GetStream();
            StreamReader sr = new StreamReader(clientStream);
            StreamWriter sw = new StreamWriter(clientStream);

            ASCIIEncoding encoder = new ASCIIEncoding();
            

            sw.Write(textBox3.Text+"\n");
            sw.Flush();

            string result = CheckPosTagger(sr.ReadLine());
            MessageBox.Show(GetSuggestedAction(result));

        }

        private void button6_Click(object sender, EventArgs e)
        {
            TcpClient client = new TcpClient();

            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5555);

            client.Connect(serverEndPoint);

            NetworkStream clientStream = client.GetStream();
            StreamReader sr = new StreamReader(clientStream);
            StreamWriter sw = new StreamWriter(clientStream);

            ASCIIEncoding encoder = new ASCIIEncoding();


            sw.Write(textBox3.Text + "\n");
            sw.Flush();

            string result = CheckPosTagger(sr.ReadLine());
            GetSuggestedActions(result);
        }

        public String CheckPosTagger(String phrase)
        {
            phrase = phrase.Replace("fight/NN", "fight/VB");
            return phrase;
        }

        public List<String> GetSuggestedActions(String phrase)
        {
            List<String> result = new List<String>();

            result = GetVerbs(phrase);

            foreach (String s in result)
            {
                MessageBox.Show(s);
            }

            return result;
        }

        public String GetSuggestedAction(String phrase)
        {
            String verb = GetValidActionName(GetVerb(phrase).Trim());                        
            String actuator = GetActuatorNoun(phrase).Trim();
            String subject = GetSubjectNoun(phrase).Trim();

            Boolean actuatorIsActor = IsActor(actuator);
            Boolean subjectIsActor = IsActor(subject);

            String action = "";

            if (verb.Equals(""))
                return "Erro: Invalid Action!";

            if (actuatorIsActor)
                actuator = GetValidActorName(actuator);
            else if (IsPlace(actuator))
                actuator = GetValidPlaceName(actuator);
            else
                return "Erro: Invalid Actuator: " + actuator;

            if (subjectIsActor)
                subject = GetValidActorName(subject);
            else if (IsPlace(subject))
                subject = GetValidPlaceName(subject);
            else
                return "Erro: Invalid Subject: " + subject;

            //Rule: CH, PL
            if ((verb.Equals("go"))||(verb.Equals("reduce_protection")))
            {
                if ((actuatorIsActor == true)&&(subjectIsActor == false))
                    action = verb + "(" + actuator + ", " + subject + ")";
                else if ((actuatorIsActor == false)&&(subjectIsActor == true))
                    action = verb + "(" + subject + ", " + actuator + ")";
                else
                    return "Erro: Invalid Action Syntax: " + verb + "(" + actuator + ", " + subject + ")";
            }
            //Rule: CH, CH
            else if ((verb.Equals("kidnap")) || (verb.Equals("kill")) || (verb.Equals("free")) || (verb.Equals("marry")) || (verb.Equals("donate")) || (verb.Equals("bewitch")))
            {
                if ((actuatorIsActor == true) && (subjectIsActor == true))
                    action = verb + "(" + actuator + ", " + subject + ")";
                else
                    return "Erro: Invalid Action Syntax: " + verb + "(" + actuator + ", " + subject + ")";
            }   
            //Rule: Attack/Fight
            else if (verb.Equals("attack"))
            {
                if ((actuatorIsActor == true) && (subjectIsActor == true))
                    action = "fight" + "(" + actuator + ", " + subject + ")";
                else if ((actuatorIsActor == true) && (subjectIsActor == false))
                    action = verb + "(" + actuator + ", " + subject + ")";
                else
                    return "Erro: Invalid Action Syntax: " + verb + "(" + actuator + ", " + subject + ")";
            }
            
            return action;
        }        

        public List<String> GetVerbs(String phrase)
        {
            List<String> result = new List<String>();
            phrase = " " + phrase;

            int vp = 0;
            int vs = 0;
            while ((vp = phrase.IndexOf("/VB", vp)) != -1)
            {
                vs = phrase.LastIndexOf(" ", vp);
                if (vs == -1) break;
                result.Add(phrase.Substring(vs, vp - vs));                              
                vp++;
            }
            return result;
        }

        public String GetVerb(String phrase)
        {
            phrase = " " + phrase;
            int vp = phrase.LastIndexOf("/VB");
            if (vp == -1)
                return "";
            int vs = phrase.LastIndexOf(" ", vp);
            if (vs == -1)
                return "";
            return phrase.Substring(vs, vp - vs);
        }

        public String GetActuatorNoun(String verb, String phrase)
        {
            phrase = " " + phrase;
            int vp = phrase.IndexOf("/NN");
            if (vp == -1)
                return "";
            int vs = phrase.LastIndexOf(" ", vp);
            if (vs == -1)
                return "";
            return phrase.Substring(vs, vp - vs);
        }

        public String GetActuatorNoun(String phrase)
        {
            phrase = " " + phrase;
            int vp = phrase.IndexOf("/NN");
            if (vp == -1)
                return "";
            int vs = phrase.LastIndexOf(" ", vp);
            if (vs == -1)
                return "";
            return phrase.Substring(vs, vp - vs);
        }

        public String GetSubjectNoun(String phrase)
        {
            phrase = " " + phrase;
            int vp = phrase.LastIndexOf("/NN");
            if (vp == -1)
                return "";
            int vs = phrase.LastIndexOf(" ", vp);
            if (vs == -1)
                return "";
            return phrase.Substring(vs, vp - vs);
        }        

        public Boolean IsActor(String name)
        {
            foreach (CharacterInfoMap charinfo in validCharacters)
            {
                if (name.ToLower().Contains(charinfo.word))
                {
                    return true;
                }
            }
            return false;
        }

        public Boolean IsPlace(String name)
        {
            foreach (PlaceInfoMap placeinfo in validPlaces)
            {
                if (name.ToLower().Contains(placeinfo.word))
                {
                    return true;
                }
            }
            return false;
        }

        public String GetValidActorName(String name)
        {
            foreach (CharacterInfoMap charinfo in validCharacters)
            {
                if (name.ToLower().Contains(charinfo.word))
                {
                    return charinfo.character;
                }
            }
            return "";
        }

        public String GetValidPlaceName(String name)
        {
            foreach (PlaceInfoMap placeinfo in validPlaces)
            {
                if (name.ToLower().Contains(placeinfo.word))
                {
                    return placeinfo.place;
                }
            }
            return "";
        }

        public String GetValidActionName(String name)
        {
            foreach (ActionInfoMap actioninfo in validActions)
            {
                if (name.ToLower().Contains(actioninfo.word))
                {
                    return actioninfo.action;
                }
            }
            return "";
        }

        public void InitCharacters()
        {
            validCharacters.Add(new CharacterInfoMap("brian", "Brian"));
            validCharacters.Add(new CharacterInfoMap("hero", "Brian"));
            validCharacters.Add(new CharacterInfoMap("knight", "Brian"));
            validCharacters.Add(new CharacterInfoMap("marian", "Marian"));
            validCharacters.Add(new CharacterInfoMap("princess", "Marian"));
            validCharacters.Add(new CharacterInfoMap("lady", "Marian"));
            validCharacters.Add(new CharacterInfoMap("draco", "Draco"));
            validCharacters.Add(new CharacterInfoMap("dragon", "Draco"));
            validCharacters.Add(new CharacterInfoMap("villain", "Draco"));
            validCharacters.Add(new CharacterInfoMap("hoel", "Hoel"));
            validCharacters.Add(new CharacterInfoMap("turjan", "Turjan"));
            validCharacters.Add(new CharacterInfoMap("mage", "Turjan"));            
        }

        public void InitPlaces()
        {
            validPlaces.Add(new PlaceInfoMap("red castle", "Red Castle"));
            validPlaces.Add(new PlaceInfoMap("dragon castle", "Red Castle"));
            validPlaces.Add(new PlaceInfoMap("villain castle", "Red Castle"));
            validPlaces.Add(new PlaceInfoMap("gray castle", "Gray Castle"));
            validPlaces.Add(new PlaceInfoMap("hero castle", "Gray Castle"));
            validPlaces.Add(new PlaceInfoMap("white palace", "White Palace"));
            validPlaces.Add(new PlaceInfoMap("princess palace", "White Palace"));
            validPlaces.Add(new PlaceInfoMap("princess castle", "White Palace"));
            validPlaces.Add(new PlaceInfoMap("green forest", "Green Forest"));
            validPlaces.Add(new PlaceInfoMap("mage forest", "Green Forest"));
            validPlaces.Add(new PlaceInfoMap("mage castle", "Green Forest"));
            validPlaces.Add(new PlaceInfoMap("church", "Church"));
        }

        public void InitActions()
        {
            validActions.Add(new ActionInfoMap("go", "go"));
            validActions.Add(new ActionInfoMap("goes", "go"));
            validActions.Add(new ActionInfoMap("going", "go"));            
            validActions.Add(new ActionInfoMap("abscond", "go"));
            validActions.Add(new ActionInfoMap("absconded", "go"));
            validActions.Add(new ActionInfoMap("absconding", "go"));            
            validActions.Add(new ActionInfoMap("depart", "go"));
            validActions.Add(new ActionInfoMap("departing", "go"));
            validActions.Add(new ActionInfoMap("departed", "go"));
            validActions.Add(new ActionInfoMap("escape", "go"));
            validActions.Add(new ActionInfoMap("escaped", "go"));
            validActions.Add(new ActionInfoMap("escaping", "go"));
            validActions.Add(new ActionInfoMap("exit", "go"));
            validActions.Add(new ActionInfoMap("exiting", "go"));
            validActions.Add(new ActionInfoMap("exited", "go"));
            validActions.Add(new ActionInfoMap("flee", "go"));
            validActions.Add(new ActionInfoMap("fleeing", "go"));
            validActions.Add(new ActionInfoMap("fled", "go"));
            validActions.Add(new ActionInfoMap("fly", "go"));
            validActions.Add(new ActionInfoMap("flying", "go"));
            validActions.Add(new ActionInfoMap("flied", "go"));
            validActions.Add(new ActionInfoMap("get away", "go"));
            validActions.Add(new ActionInfoMap("get going", "go"));
            validActions.Add(new ActionInfoMap("get lost", "go"));
            validActions.Add(new ActionInfoMap("get off", "go"));
            validActions.Add(new ActionInfoMap("hit the road", "go"));
            validActions.Add(new ActionInfoMap("journey", "go"));
            validActions.Add(new ActionInfoMap("lam", "go"));
            validActions.Add(new ActionInfoMap("leave", "go"));
            validActions.Add(new ActionInfoMap("leaving", "go"));
            validActions.Add(new ActionInfoMap("move", "go"));
            validActions.Add(new ActionInfoMap("moved", "go"));
            validActions.Add(new ActionInfoMap("moving", "go"));
            validActions.Add(new ActionInfoMap("move out", "go"));
            validActions.Add(new ActionInfoMap("pass", "go"));
            validActions.Add(new ActionInfoMap("progress", "go"));
            validActions.Add(new ActionInfoMap("pull out", "go"));
            validActions.Add(new ActionInfoMap("push off", "go"));
            validActions.Add(new ActionInfoMap("quit", "go"));
            validActions.Add(new ActionInfoMap("retire", "go"));
            validActions.Add(new ActionInfoMap("run", "go"));
            validActions.Add(new ActionInfoMap("run away", "go"));
            validActions.Add(new ActionInfoMap("set off", "go"));
            validActions.Add(new ActionInfoMap("shove off", "go"));
            validActions.Add(new ActionInfoMap("skip out", "go"));
            validActions.Add(new ActionInfoMap("take off", "go"));
            validActions.Add(new ActionInfoMap("take flight", "go"));
            validActions.Add(new ActionInfoMap("travel", "go"));
            validActions.Add(new ActionInfoMap("wend", "go"));

            validActions.Add(new ActionInfoMap("kidnap", "kidnap"));
            validActions.Add(new ActionInfoMap("kidnapping", "kidnap"));
            validActions.Add(new ActionInfoMap("kidnaped", "kidnap"));
            validActions.Add(new ActionInfoMap("abduct", "kidnap"));
            validActions.Add(new ActionInfoMap("abducted", "kidnap"));
            validActions.Add(new ActionInfoMap("abducting", "kidnap"));
            validActions.Add(new ActionInfoMap("capture", "kidnap"));
            validActions.Add(new ActionInfoMap("capturing", "kidnap"));
            validActions.Add(new ActionInfoMap("captured", "kidnap"));
            validActions.Add(new ActionInfoMap("carry away", "kidnap"));
            validActions.Add(new ActionInfoMap("carry off", "kidnap"));
            validActions.Add(new ActionInfoMap("coax", "kidnap"));
            validActions.Add(new ActionInfoMap("decoy", "kidnap"));
            validActions.Add(new ActionInfoMap("entice", "kidnap"));
            validActions.Add(new ActionInfoMap("grab", "kidnap"));
            validActions.Add(new ActionInfoMap("grabbing", "kidnap"));
            validActions.Add(new ActionInfoMap("grabbed", "kidnap"));
            validActions.Add(new ActionInfoMap("hijack", "kidnap"));
            validActions.Add(new ActionInfoMap("lure", "kidnap"));
            validActions.Add(new ActionInfoMap("run away with", "kidnap"));
            validActions.Add(new ActionInfoMap("seduce", "kidnap"));
            validActions.Add(new ActionInfoMap("seize", "kidnap"));
            validActions.Add(new ActionInfoMap("seizes", "kidnap"));
            validActions.Add(new ActionInfoMap("seizing", "kidnap"));
            validActions.Add(new ActionInfoMap("seized", "kidnap"));
            validActions.Add(new ActionInfoMap("snatch", "kidnap"));
            validActions.Add(new ActionInfoMap("steal", "kidnap"));
            validActions.Add(new ActionInfoMap("sequester", "kidnap"));
            validActions.Add(new ActionInfoMap("sequestrate", "kidnap"));

            //Fight and Attack = if NN is a place = Attack, If NN is character = Fight
            validActions.Add(new ActionInfoMap("attack", "attack"));
            validActions.Add(new ActionInfoMap("attacking", "attack"));
            validActions.Add(new ActionInfoMap("attacked", "attack"));
            validActions.Add(new ActionInfoMap("aggress", "attack"));
            validActions.Add(new ActionInfoMap("aggressing", "attack"));
            validActions.Add(new ActionInfoMap("aggressed", "attack"));
            validActions.Add(new ActionInfoMap("assail", "attack"));
            validActions.Add(new ActionInfoMap("assault", "attack"));
            validActions.Add(new ActionInfoMap("assaulting", "attack"));
            validActions.Add(new ActionInfoMap("assaulted", "attack"));
            validActions.Add(new ActionInfoMap("bash", "attack"));
            validActions.Add(new ActionInfoMap("bat", "attack"));
            validActions.Add(new ActionInfoMap("beat", "attack"));
            validActions.Add(new ActionInfoMap("biff", "attack"));
            validActions.Add(new ActionInfoMap("bop", "attack"));
            validActions.Add(new ActionInfoMap("bust", "attack"));
            validActions.Add(new ActionInfoMap("combat", "attack"));
            validActions.Add(new ActionInfoMap("combating", "attack"));
            validActions.Add(new ActionInfoMap("combated", "attack"));
            validActions.Add(new ActionInfoMap("harm", "attack"));
            validActions.Add(new ActionInfoMap("harming", "attack"));
            validActions.Add(new ActionInfoMap("hit", "attack"));
            validActions.Add(new ActionInfoMap("hitting", "attack"));            
            validActions.Add(new ActionInfoMap("hurt", "attack"));
            validActions.Add(new ActionInfoMap("hurting", "attack"));
            validActions.Add(new ActionInfoMap("kick", "attack"));
            validActions.Add(new ActionInfoMap("kicking", "attack"));
            validActions.Add(new ActionInfoMap("kicked", "attack"));
            validActions.Add(new ActionInfoMap("molest", "attack"));
            validActions.Add(new ActionInfoMap("molesting", "attack"));
            validActions.Add(new ActionInfoMap("punch", "attack"));
            validActions.Add(new ActionInfoMap("punching", "attack"));
            validActions.Add(new ActionInfoMap("slog", "attack"));
            validActions.Add(new ActionInfoMap("stab", "attack"));
            validActions.Add(new ActionInfoMap("strike", "attack"));
            validActions.Add(new ActionInfoMap("wallop", "attack"));
            validActions.Add(new ActionInfoMap("whop", "attack"));
            validActions.Add(new ActionInfoMap("fight", "attack"));
            validActions.Add(new ActionInfoMap("fighting", "attack"));
            validActions.Add(new ActionInfoMap("challenge", "attack"));
            validActions.Add(new ActionInfoMap("altercate", "attack"));
            validActions.Add(new ActionInfoMap("battle", "attack"));
            validActions.Add(new ActionInfoMap("bicker", "attack"));
            validActions.Add(new ActionInfoMap("brawl", "attack"));
            validActions.Add(new ActionInfoMap("contend", "attack"));
            validActions.Add(new ActionInfoMap("dispute", "attack"));
            validActions.Add(new ActionInfoMap("duel", "attack"));
            validActions.Add(new ActionInfoMap("dueling", "attack"));
            validActions.Add(new ActionInfoMap("grapple", "attack"));
            validActions.Add(new ActionInfoMap("joust", "attack"));
            validActions.Add(new ActionInfoMap("quarrel", "attack"));
            validActions.Add(new ActionInfoMap("scrap", "attack"));
            validActions.Add(new ActionInfoMap("scuffle", "attack"));
            validActions.Add(new ActionInfoMap("strive", "attack"));
            validActions.Add(new ActionInfoMap("struggle", "attack"));
            validActions.Add(new ActionInfoMap("war", "attack"));
            validActions.Add(new ActionInfoMap("wrestle", "attack"));
            validActions.Add(new ActionInfoMap("wrestling", "attack"));

            validActions.Add(new ActionInfoMap("kill", "kill"));
            validActions.Add(new ActionInfoMap("killing", "kill"));
            validActions.Add(new ActionInfoMap("killed", "kill"));
            validActions.Add(new ActionInfoMap("annihilate", "kill"));
            validActions.Add(new ActionInfoMap("asphyxiate", "kill"));
            validActions.Add(new ActionInfoMap("assassinate", "kill"));
            validActions.Add(new ActionInfoMap("crucify", "kill"));
            validActions.Add(new ActionInfoMap("dispatch", "kill"));
            validActions.Add(new ActionInfoMap("drown", "kill"));
            validActions.Add(new ActionInfoMap("electrocute", "kill"));
            validActions.Add(new ActionInfoMap("eradicate", "kill"));
            validActions.Add(new ActionInfoMap("erase", "kill"));
            validActions.Add(new ActionInfoMap("execute", "kill"));
            validActions.Add(new ActionInfoMap("exterminate", "kill"));
            validActions.Add(new ActionInfoMap("extirpate", "kill"));
            validActions.Add(new ActionInfoMap("finish", "kill"));
            validActions.Add(new ActionInfoMap("guillotine", "kill"));
            validActions.Add(new ActionInfoMap("liquidate", "kill"));
            validActions.Add(new ActionInfoMap("massacre", "kill"));
            validActions.Add(new ActionInfoMap("murder", "kill"));
            validActions.Add(new ActionInfoMap("neutralize", "kill"));
            validActions.Add(new ActionInfoMap("obliterate", "kill"));
            validActions.Add(new ActionInfoMap("poison", "kill"));
            validActions.Add(new ActionInfoMap("sacrifice", "kill"));
            validActions.Add(new ActionInfoMap("slaughter", "kill"));
            validActions.Add(new ActionInfoMap("slay", "kill"));
            validActions.Add(new ActionInfoMap("smother", "kill"));
            validActions.Add(new ActionInfoMap("strangle", "kill"));
            validActions.Add(new ActionInfoMap("suffocate", "kill"));
            validActions.Add(new ActionInfoMap("strangle", "kill"));
            validActions.Add(new ActionInfoMap("zap", "kill"));
            validActions.Add(new ActionInfoMap("eliminate", "kill"));
            validActions.Add(new ActionInfoMap("destroy", "kill"));

            validActions.Add(new ActionInfoMap("free", "free"));
            validActions.Add(new ActionInfoMap("liberate", "free"));
            validActions.Add(new ActionInfoMap("let go", "free"));
            validActions.Add(new ActionInfoMap("absolve", "free"));
            validActions.Add(new ActionInfoMap("acquit", "free"));
            validActions.Add(new ActionInfoMap("bail", "free"));
            validActions.Add(new ActionInfoMap("discharge", "free"));
            validActions.Add(new ActionInfoMap("dismiss", "free"));
            validActions.Add(new ActionInfoMap("emancipate", "free"));
            validActions.Add(new ActionInfoMap("enfranchise", "free"));
            validActions.Add(new ActionInfoMap("loose", "free"));
            validActions.Add(new ActionInfoMap("loosen", "free"));
            validActions.Add(new ActionInfoMap("pardon", "free"));
            validActions.Add(new ActionInfoMap("parole", "free"));
            validActions.Add(new ActionInfoMap("ransom", "free"));
            validActions.Add(new ActionInfoMap("redeem", "free"));
            validActions.Add(new ActionInfoMap("release", "free"));
            validActions.Add(new ActionInfoMap("relieve", "free"));
            validActions.Add(new ActionInfoMap("rescue", "free"));
            validActions.Add(new ActionInfoMap("save", "free"));
            validActions.Add(new ActionInfoMap("set free", "free"));
            validActions.Add(new ActionInfoMap("uncage", "free"));
            validActions.Add(new ActionInfoMap("unchain", "free"));
            validActions.Add(new ActionInfoMap("uncage", "free"));
            validActions.Add(new ActionInfoMap("unfetter", "free"));
            validActions.Add(new ActionInfoMap("unfix", "free"));
            validActions.Add(new ActionInfoMap("unleash", "free"));
            validActions.Add(new ActionInfoMap("untie", "free"));
                   
            validActions.Add(new ActionInfoMap("bewitch", "bewitch"));
            validActions.Add(new ActionInfoMap("charm", "bewitch"));
            validActions.Add(new ActionInfoMap("bedevil", "bewitch"));
            validActions.Add(new ActionInfoMap("control", "bewitch"));
            validActions.Add(new ActionInfoMap("dazzle", "bewitch"));
            validActions.Add(new ActionInfoMap("enchant", "bewitch"));
            validActions.Add(new ActionInfoMap("enthrall", "bewitch"));
            validActions.Add(new ActionInfoMap("hypnotize", "bewitch"));
            validActions.Add(new ActionInfoMap("spellbind", "bewitch"));
            validActions.Add(new ActionInfoMap("trick", "bewitch"));
            validActions.Add(new ActionInfoMap("voodoo", "bewitch"));

            validActions.Add(new ActionInfoMap("donate", "donate"));
            validActions.Add(new ActionInfoMap("bless", "donate"));

            validActions.Add(new ActionInfoMap("reduce", "reduce_protection"));

            validActions.Add(new ActionInfoMap("marry", "marry"));
            validActions.Add(new ActionInfoMap("couple", "marry"));
            validActions.Add(new ActionInfoMap("wed", "marry"));
        }     
    }
}
