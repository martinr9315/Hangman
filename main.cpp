#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <utility>
using namespace std;

void printMessage(string m, bool top, bool bottom)
{
    if (top)
        cout<< "+------------------------------+"<<endl;
    cout<< "|";
        bool front = true;
        for (int i=m.length(); i<30; i++)
        {
            if (front)
                m = " "+m;
            else
                m = m+" ";
            front = !front;
        }
        cout << m << "|"<<endl;
    
    if (bottom)
         cout<< "+------------------------------+"<<endl;
    
}

void drawHangman(int guesses)
{
    if (guesses>=1)
        printMessage("|", false, false);
    else
        printMessage("", false, false);
    if (guesses>=2)
        printMessage("|", false, false);
    else
           printMessage("", false, false);
    if (guesses>=3)
        printMessage("O", false, false);
    else
           printMessage("", false, false);
    
    if (guesses>=6)
        printMessage("/|\\", false, false);
    else if (guesses==5)
        printMessage("/|", false, false);
    else if (guesses>=4)
        printMessage("|", false, false);
    else
           printMessage("", false, false);
    
    if (guesses==7)
        printMessage("/ ", false, true);
    else if (guesses==8)
        printMessage("/ \\", false, true);
    else
        printMessage("", false, true);
}

bool printAlphabet(string &alphaLeft1, string &alphaLeft2, char guess)
{
    bool unguessed = false;
    for (int i=0; i<alphaLeft1.length(); i++)
    {
        if (alphaLeft1[i] == toupper(guess))
        {
            alphaLeft1[i]=' ';
            unguessed = true;
        }
    }
    for (int i=0; i<alphaLeft2.length(); i++)
    {
        if (alphaLeft2[i] == toupper(guess))
        {
            alphaLeft2[i]=' ';
            unguessed = true;
        }
    }
    
    if (unguessed)
    {
        printMessage("Available letters:", true, false);
        printMessage(alphaLeft1, false, false);
        printMessage(alphaLeft2, false, true);
        return unguessed;
    }
    
    string m ="Already guessed ";
    m+=guess;
    printMessage(m, true, true);
    return false;
}

bool checkWord(string mysteryWord, string &playerWord, char guess)
{
    bool contains = false;
    for (int i=0; i<mysteryWord.length(); i++)
    {
        if (toupper(mysteryWord[i]) == toupper(guess))
        {
            playerWord[i]=guess;
            contains = true;
        }
    }
    return contains;
}

int randInt(int min, int max)
{
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::default_random_engine generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

string getRandomWord()
{
    string wordList[100] = {"Adult", "Aeroplane", "Airforce", "Airport","Album", "Alphabet", "Backpack","Balloon" , "Banana" , "Barbecue", "Bathroom", "Bathtub","Bottle","Bowl","Box","Boy","Brain", "Bridge","Butterfly","Button", "Cappuccino","Car","Carpet", "Carrot", "Cave","Chair", "Chess", "Chief", "Chisel", "Chocolates","Circle", "Circus", "Clock" ,"Clown", "Coffee", "Comet", "Compass", "Computer" , "Crystal" , "Diamond" ,"Dress" , "Drill", "Drum" , "Dung", "Eggplant", "Earth", "Electricity", "Elephant", "Eraser","Explosive", "Feather", "Festival" , "Film", "Floodlight", "Freeway", "Fungus","Gemstone", "Hieroglyph", "Highway", "Horoscope" ,"heartbreaking", "Kaleidoscope", "Meteor", "Microscope", "Milkshake", "Mosquito", "Parachute", "Passport","Pendulum","Pyramid","Radar","Rainbow", "Saddle", "Sandpaper","Satellite", "Signature","Skeleton","Software","Spectrum","Surveyor","Tapestry","Thermometer", "Torpedo","Treadmill", "Typewriter", "Vacuum", "Vulture", "Wheelchair", "Xylophone", "Zebra","receptive","jolly","impulse","assorted","amuck","squalid","economic","ethereal","arithmetic","spooky"};
    
    int r = randInt(0,99);
    return wordList[r];
}

 
int main()
{
    printMessage("HANGMAN", true, true);
    string alphabet1 = "A B C D E F G H I J K L M";
    string alphabet2 = "N O P Q R S T U V W X Y Z";
    string mysteryWord = getRandomWord();
    string playerWord = "";
    for (int i=0; i<mysteryWord.length(); i++)
    {
        mysteryWord[i]=toupper(mysteryWord[i]);
        playerWord += "_";
    }
    int tries = 0;
    
    while (playerWord!= mysteryWord && tries<8)
    {
        cout<<"Guess a letter: ";
        string g;
        getline (cin, g);
        char guess = toupper(g[0]);
        if (!isalpha(guess))
        {
            printMessage("Guess must be a letter", true, true);
            continue;
        }
        if (printAlphabet(alphabet1, alphabet2, guess) && !checkWord(mysteryWord, playerWord, guess))
            tries++;
        
        drawHangman(tries);
        printMessage(playerWord, false, true);
    }
    
    if (tries >= 8)
        printMessage("You lost :(", true, true);
    else
        printMessage("You won!!!", true, true);
}
