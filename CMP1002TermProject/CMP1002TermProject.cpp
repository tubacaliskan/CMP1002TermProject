//NOTES TO OUR PROFESSOR:
//OUR IMPLEMENTATION OF MAGIC THE GATHERING IS MOSTLY BASED ON STRINGS, SO MOST OF THE TIME WE WILL ASK YOU TO WRITE CARD NAMES, FOR EX. IF YOU WOULD LIKE TO PLAY ARMORED PEGASUS USE SHOULD WRITE ITS NAME AS YOU SEEN ON THE SCREEN (ArmoredPegasus)
//OUR GAME ALSO HAS SUMMONNING SICKNESS
//CREATURE CARDS GET BACK TO ITS HP IN UNTAP PHASE
//ALL SUMMONNING EFFECTS GIVE EFFECT ONLY ONES - WE CHECK IT
//ALL ENCHANTMENT EFFECTS GIVE EFFECT EACH TURN UNTIL ENCHANTMENT CARD DIES BY DISENCHANT OR ITS CREATURE CARD DIES
//WE REALLY TRIED OUR BEST TO IMPLEMENT THE GAME AS CLOSE AS REAL ONE AND YOUR REQUESTS, BUT SINCE THE REAL GAME HAS GUI AND WE DON'T WE TRIED TO MAKE THE PLAYERS AS FREE AS POSSIBLE THATS WHY WE ASK MANY QUESTIONS EACH TURN.
//WE HOPE YOU LIKE OUR GAME :)

#include <iostream>
//#include <stdio.h>
//#include <conio.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> //saat seed
#include <typeinfo> //class name
#include <stdlib.h>

#define getch() wgetch(stdscr) //nerde get ch görürsen sağ taraftaini yaz

class Effect;
class Card;
class Player;
class Game;


//vektörü kesmeye yarıyor.
template<typename T>
std::vector<T> slice(std::vector<T>& v, int  m, int n) {
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
    std::vector<T> vec(first, last);
    v.erase(first, last);
    return vec;
}


class Effect {
protected:
    Card* card;
public:

    friend class Game;
};
/*
class allWhiteCreaturesGainPlus1: public Effect{
protected:
public:

    void _allWhiteCreaturesGainPlus1();

};
*/
class Card {
protected:
    std::string cardType;
    int   manaCost2;
    //Player *player; //kullanmadık
    std::string name;
    std::vector<std::string> manaCost;
    std::string cardColor;
    bool isDestroyed;
    int manaCostG = 0; // GREEN
    int manaCostL = 0; //BLUE
    int manaCostR = 0; //RED
    int manaCostW = 0; //WHITE
    int manaCostB = 0; //BLACK
    int manaCostC = 0; //COLORLESS
    std::string a;
    int attackPower;
    int hp;
    int baseHp;
    std::shared_ptr<Card>ptr;
    std::string ability;

public:
    Card() {} //default const.

    Card(std::string _name, std::vector<std::string> _manaCost, std::string _cardColor, int _attackPower, int _hp, int _baseHp, std::string _ability) :name(_name), attackPower(_attackPower), hp(_hp), baseHp(_baseHp), ability(_ability) {  //constructor

        for (int i = 0; i < _manaCost.size(); i++) {

            manaCost.push_back(_manaCost[i]);

            // her kartın manasının sayısı
            if (_manaCost[i] == "G") {
                manaCostG = manaCostG + 1;
            }
            else if (_manaCost[i] == "L") {
                manaCostL = manaCostL + 1;
            }
            else if (_manaCost[i] == "R") {
                manaCostR = manaCostR + 1;
            }
            else if (_manaCost[i] == "W") {
                manaCostW = manaCostW + 1;
            }
            else if (_manaCost[i] == "B") {
                manaCostB = manaCostB + 1;
            }
            else {
                manaCostC = manaCostC + 1; //colorless sayısı
            }

        }
        manaCost2 = _manaCost.size();
        cardColor = _cardColor;
    }

    Card(const Card& c) {

        name = c.name;
        manaCost2 = c.manaCost.size();
        cardColor = c.cardColor;
        for (int i = 0; i < c.manaCost.size(); i++) {

            manaCost.push_back(c.manaCost[i]);

            // her kartın manasının sayısı
            if (c.manaCost[i] == "G") {
                manaCostG = manaCostG + 1;
            }
            else if (c.manaCost[i] == "L") {
                manaCostL = manaCostL + 1;
            }
            else if (c.manaCost[i] == "R") {
                manaCostR = manaCostR + 1;
            }
            else if (c.manaCost[i] == "W") {
                manaCostW = manaCostW + 1;
            }
            else if (c.manaCost[i] == "B") {
                manaCostB = manaCostB + 1;
            }
            else {
                manaCostC = manaCostC + 1; //colorless sayısı
            }
        }
    }

    ~Card() {}

    //card name i alan ve yazdıran fonksiyon
    static void printCard(const Card& a) {
        std::cout << "--------------------" << std::endl;
        std::cout << " card name: " << a.name << std::endl;
        std::cout << " |GREEN mana: " << a.manaCostG;
        std::cout << " |BLUE mana: " << a.manaCostL;
        std::cout << " |RED mana: " << a.manaCostR;
        std::cout << " |WHITE mana: " << a.manaCostW;
        std::cout << " |BLACK mana: " << a.manaCostB;
        std::cout << " |COLORLESS mana: " << a.manaCostC;
        std::cout << " |Total mana: " << a.manaCost2 << std::endl;
    }

    // printCar fonksiyonunu kullanarak kullanıcının deck'ini basan fonksiyon
    static void printDeck(const std::vector<std::shared_ptr<Card>>& b) {
        for (const auto& item : b) {
            printCard(*item);
        }
    }
    //string olarak vektör basan fonksiyon - mana için
    static void printManaVector(const std::vector<std::string>& _manaVector) {
        for (const auto& item1 : _manaVector) {
            std::cout << item1 << std::endl;;
        }
    }
    static void printCardApHp(const Card& a) {
        std::cout << "--------------------" << std::endl;
        std::cout << " card name: " << a.name << std::endl;
        std::cout << "Attack Power: " << a.attackPower;
        std::cout << ", HP: " << a.hp << std::endl;
    }
    static void printDeckPower(const std::vector<std::shared_ptr<Card>>& b) {
        for (const auto& item : b) {
            printCardApHp(*item);
        }
    }

    static void printDiscard(const Card& a) {
        std::cout << " card name: " << a.name << std::endl;
    }
    static void printDeckDiscard(const std::vector<std::shared_ptr<Card>>& b) {
        for (const auto& item : b) {
            printDiscard(*item);
        }
    }
    virtual void play() {
        //other cards will inherit and implement different things on this function based on their speciality
    }
    static std::string getName(const Card& a) {
        return a.name;
    }
    static std::string getCardType(const Card& a) {
        return a.cardType;
    }
    static int getCardHp(const Card& a) {
        return a.hp;
    }
    static int getCardAttackPower(const Card& a) {
        return a.attackPower;
    }
    static  int getCardBaseHp(const Card& a) {
        return a.baseHp;
    }

    static void setAbility(Card& a, std::string newAbility) {
        a.ability = newAbility;
    }

    //Seçilen card üzerinden mana vektörüne ulaşıp current mananın sub elemanı olup olmadığını kontrol eden fonksiyon
    static bool compare(Card a, std::vector<std::string>_currentMana) {
        int colorlessCount = 0;
        for (auto outer_iterator = a.manaCost.begin(); outer_iterator != a.manaCost.end(); ++outer_iterator) {
            if (*outer_iterator != "C") {
                bool isFound = false;
                for (auto inner_iterator = _currentMana.begin(); inner_iterator != _currentMana.end(); ++inner_iterator) {
                    if (*outer_iterator == *inner_iterator) {
                        isFound = true;
                        inner_iterator = _currentMana.erase(inner_iterator);
                        break;
                    }
                }
                if (isFound == false) {
                    return false;
                }
            }
            else {
                ++colorlessCount;
            }
        }
        return (_currentMana.size() - a.manaCost.size()) >= colorlessCount;
    }

    friend class Player;
    friend class Game;
};

class CreatureCard :public Card {
protected:
    //int attackPower;
    //int hp;
    //int baseHp;
    //std::string givenAbility;
    //bool isDestroyed;

public:
    CreatureCard() {}

    CreatureCard(std::string _name, std::vector<std::string> _manaCost, std::string _cardColor, int _attackPower, int _hp, int _baseHp, std::string _ability) : Card(_name, _manaCost, _cardColor, _attackPower, _hp, _baseHp, _ability) {
        cardType = "CreatureCard";
        ptr = NULL;
    }

    CreatureCard(const CreatureCard& c) : Card(c) {
        attackPower = c.attackPower;
        hp = c.hp;
        baseHp = c.baseHp;
        ability = c.ability;
        cardType = "CreatureCard";
        ptr = c.ptr;
    }

    ~CreatureCard() {}
    friend class SorceryCard; //??????????????????????????
    friend class Game;   //??????????????????????????
};

class SorceryCard :public Card {
protected:
    //Effect sorcery_effect;

public:
    SorceryCard() {}

    SorceryCard(std::string _name, std::vector<std::string> _manaCost, std::string _cardColor) : Card(_name, _manaCost, _cardColor, 0, 0, 0, " ") {
        cardType = "SorceryCard";
        ptr = NULL;
    }

    SorceryCard(const SorceryCard& c) : Card(c) {
        cardType = "SorceryCard";
        ptr = c.ptr;
    }

    /* void allWhiteCreaturesGainPlus1(CreatureCard &c){
         if(c.cardColor=="WHITE"){
             c.hp = c.hp +1;
             c.attackPower = c.attackPower+1;
         }

     } */

    ~SorceryCard() {}
};

class EnchantmentCard :public Card {
protected:
    //Effect enchantment_effect;

public:
    EnchantmentCard() {}

    EnchantmentCard(std::string _name, std::vector<std::string> _manaCost, std::string _cardColor) : Card(_name, _manaCost, _cardColor, 0, 0, 0, " ") {
        cardType = "EnchantmentCard";
        ptr = NULL;
    }
    EnchantmentCard(const EnchantmentCard& c) : Card(c) {
        cardType = "EnchantmentCard";
        ptr = c.ptr;
    }

    ~EnchantmentCard() {}
};

class LandCard :public Card {
protected:
    //std::string cardType;
    bool isTapped = false;
public:
    LandCard(std::string _name, std::vector<std::string> _manaCost, std::string _cardColor) : Card(_name, _manaCost, _cardColor, 0, 0, 0, " ") {
        cardType = "LandCard";
        ptr = NULL;
    }

    LandCard(const LandCard& c) : Card(c) {
        cardType = "LandCard";
        ptr = c.ptr;
    }

    ~LandCard() {}
};

class Player {

protected:
    std::vector<std::string> currentManaCost;
    Game* game; //kullanılmıyor
    std::string playerName;
    std::vector<std::shared_ptr<Card>> playerLibraryDeck;
    std::vector<std::shared_ptr<Card>> playerHandDeck;
    std::vector<std::shared_ptr<Card>> playerPlayDeck;
    std::vector<std::shared_ptr<Card>> playerPlayDeck2; //bu land cardların tekrar untap olması için
    std::vector<std::shared_ptr<Card>> playerPlayDeckCreatureRound;//creature card summonning sickness için
    std::vector<std::shared_ptr<Card>> playerCombatDeck;
    std::vector<std::shared_ptr<Card>> playerDiscardDeck;
    std::vector<std::shared_ptr<Card>> playerDefendDeck;
    std::vector<std::shared_ptr<Card>> temporaryCreatureDeck;
    std::vector<std::shared_ptr<Card>> isLandCardPlayed;
    std::vector<std::shared_ptr<Card>> isEnchantmentEffectsOnes;//each ench. effect must work/update only for 1 time in 1 turn for a realistic game play, so that in play2 if a creature has low hp (hp's also turn to  base hp only ones in untap phase for current player ) then deals with -hp from an enchant card it should die.
    std::vector<std::shared_ptr<Card>> isEnchantmentEffectsOnes2;
    std::vector<std::shared_ptr<Card>> playerSorceryDeck;


    //bool flag;
    //int number;
    int playerHitPoint;

public:
    Player() {}

    Player(const Player& p) {
        playerName = p.playerName;
        playerHitPoint = p.playerHitPoint;
        for (int i = 0; i < p.playerLibraryDeck.size(); i++) {
            playerLibraryDeck.push_back(p.playerLibraryDeck[i]);
        }
        for (int i = 0; i < p.playerHandDeck.size(); i++) {
            playerHandDeck.push_back(p.playerHandDeck[i]);
        }
    }

    ~Player() {}

    Player(std::string _playerName, std::vector<std::shared_ptr<Card>> _playerLibraryDeck) : playerName(_playerName) {
        playerHitPoint = 15;

        for (int i = 0; i < _playerLibraryDeck.size(); i++) {
            playerLibraryDeck.push_back(_playerLibraryDeck[i]);
        }

        //std::cout<<" Printing Player " <<playerName <<"'s Cards "<< std::endl;
        //Card::printDeck(playerLibraryDeck);
        // std::cout<< "  "<< std::endl;

        //random seed generator
        unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();

        //playerLibraryDeck kartlarını karıştır
        shuffle(playerLibraryDeck.begin(), playerLibraryDeck.end(), std::default_random_engine(seed));

        //random  generator playerLibraryDeck kartlarını karıştır

        //std::cout<<" Printing Player " <<playerName <<"'s Cards - Suffled " << std::endl;
        //Card::printDeck(playerLibraryDeck);
        //std::cout<< "  "<< std::endl;

        //player'in kütüphanesinden ilk 5 kartı hand vektörüne yolla
        playerHandDeck = slice(playerLibraryDeck, 0, 4);
        //std::cout<<" Printing Player " <<playerName <<"'s hand Cards" << std::endl;
        //Card::printDeck(playerHandDeck);
        //std::cout<< "  "<< std::endl;
        //5 azalmış library bas
        //std::cout<<" Printing Player " <<playerName <<"'s new library Cards" << std::endl;
        //Card::printDeck(playerLibraryDeck);
    }

    void PrintLastSituation(Player p) {
        std::cout << "------------------------" << std::endl;
        std::cout << p.playerName << " Hp:" << p.playerHitPoint << std::endl;
    }
    //kütüphaneden - eğer koşullar uygunsa - 1 kart çekmek ve yeni eli bastırmak
    bool drawIfYouCan() {
        if (playerLibraryDeck.size() <= 0) {
            std::cout << "you do not have any card in library" << std::endl;
            return false;
        }
        else {
            if (playerHandDeck.size() < 7) {
                auto x = playerLibraryDeck.front();
                playerHandDeck.push_back(x);
                playerLibraryDeck.erase(playerLibraryDeck.begin());
                //std::cout<<" Printing Player " << playerName <<"'s new hand Cards" << std::endl;*
                //Card::printDeck(playerHandDeck);*
                return true;
            }
            else {
                std::cout << "You can't draw a card, hand is full" << std::endl;
                return true;
                //eğer true ise zaten çekiyor eğer false ise sıra diğer aksiyona geçsin
            }
        }
    }

    //KARTI OYNA
    void playTheCard() {
        std::string cardName;
        std::cout << " Printing Player " << playerName << "'s hand Cards" << std::endl;//**
        Card::printDeck(playerHandDeck);//*
        std::cout << " Pick a card from your hand deck to play, or write 'no' if you do not wish to play any card.";
        std::cin >> cardName;
        std::string a;
        a = cardName;
        int count = 0;
        std::string temp;

        for (const auto& item : playerHandDeck) {
            temp = Card::getName(*item); //hangi karttaysa onun adını al.temp e at

            if (a == "no") {
                std::cout << "  you did not play any card " << std::endl;
                break;
            } //**if else diye break olmadan da yazılabilir.

            //EĞER KART ELİMDE VARSA
            if (temp == a) {

                //EĞER KART LAND KARTSA
                if (item->cardType == "LandCard") {
                    std::cout << " You Can Play the card .";

                    //play1 phase inde buraya at, play 2 de bu destenin boyutu 0 dan büyükse oynayamaz land kart
                    isLandCardPlayed.push_back(item);

                    //push card to play deck
                    playerPlayDeck.push_back(item);
                    //push card to play deck 2 daha sonra tap için current mana arttırırken burdan ilerliycez her oyun başı playdeck 0'lansın
                    playerPlayDeck2.push_back(item);

                    //delete item (land card) from hand vector
                    //playerHandDeck.erase(std::find(playerHandDeck.begin(),playerHandDeck.end(),item));
                    playerHandDeck.erase(playerHandDeck.begin() + count);
                    std::cout << "- NEW PLAY DECK -" << std::endl;
                    Card::printDeck(playerPlayDeck);
                    std::cout << "- NEW HAND DECK - " << std::endl;
                    Card::printDeck(playerHandDeck);
                    break;
                    //turn değişicek BUNU GAME DE YAP
                }
                else { //eğer land kard değilse
                    std::cout << "you choose a non - land card " << std::endl;
                    std::cout << "How many land cards would you like to tap " << std::endl;
                    int howManyToTap;
                    std::cin >> howManyToTap;
                    int a;
                    a = playerPlayDeck.size();
                    if (howManyToTap <= a) {
                        for (int g = 0; g < howManyToTap; g++) {

                            std::cout << " Choose your " << g + 1 << ". land card to tap from inPlay Deck, that you want to use its manas" << std::endl;
                            std::string landCardToTap;
                            std::cin >> landCardToTap;
                            std::string tempMana;
                            int count3 = 0;


                            for (const auto& itemMana : playerPlayDeck2) {
                                tempMana = Card::getName(*itemMana);

                                if (tempMana == landCardToTap && itemMana->cardType == "LandCard") {

                                    //2- varsa onun manasını al ve current manaya pushla
                                    currentManaCost.push_back(itemMana->manaCost[0]);
                                    std::cout << " current mana that you have is " << std::endl;
                                    Card::printManaVector(currentManaCost);
                                    playerPlayDeck2.erase(playerPlayDeck2.begin() + count3);
                                    break;
                                }
                                else if (count3 == playerPlayDeck2.size() - 1) {
                                    std::cout << "you choose a non-land card, or you do not have this card." << std::endl;
                                    g--; //???????
                                    break; //aslında tekrar fonksiyonun başına gitmesi lazım
                                }
                                count3++;
                            }
                            //buraya not found in play2 deck dememiz lazım
                        }
                        //***TAP TAP TAP TAP
                    }

                    else {
                        std::cout << " you do not have that many land cards " << std::endl;
                        break;//?????????????????????????????????????????????
                    }

                    //LAND KART DIŞINDA KARTLAR İÇİN CURRENT MANA CHECK ET
                    if (Card::compare(*item, currentManaCost)) {

                        std::cout << " You Can Play the card .";
                        //colorless mana gerekliyse
                        if (item->manaCostC > 0) {
                            //çıkması gereken renkli land cardları bulup 2 loop içinde , çıkar.
                            for (const auto& iter1 : item->manaCost) {
                                int count2 = 0;
                                for (const auto& iter2 : currentManaCost) {

                                    if (iter1 == iter2) {
                                        currentManaCost.erase(currentManaCost.begin() + count2);
                                        break;
                                    }
                                    count2++;
                                }
                            }
                            //çıkması gereken colorless land kart için kartlar seç ve çıkar
                            for (int i = 0; i < item->manaCostC; i++) {
                                std::string temp2;
                                //std::vector<std::string> temp2Vec;
                                std::cout << "which land card you like to play for colorless" << std::endl; //tap fonksi
                                std::cin >> temp2;

                                //temp2Vec.push_back(temp2); //bunun içinde colorless için kullanmak istediği kartların adı var.
                                //***
                                if (temp2 == "Plains") {

                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "W") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "W");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için plains kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found, or you might used it already as color card " << std::endl;
                                        i--;
                                        // break;
                                    }

                                }
                                else if (temp2 == "Forest") {
                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "G") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "G");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için forest kullanıldı" << std::endl;
                                        // break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found, or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }
                                }
                                else if (temp2 == "Island") {
                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "L") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "L");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için ısland kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found  or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }

                                }
                                else if (temp2 == "Mountain") {
                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "R") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "R");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için Mountain kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found  or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }
                                }
                                else if (temp2 == "Swamp") {

                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "B") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "B");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için swamp kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found  or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }
                                }
                                else {
                                    std::cout << "Element not found" << std::endl;
                                    i--;
                                }
                            }

                            //push creature card to play deck ***aşağıda yap
                            playerPlayDeck.push_back(item);
                            //elden çıkar for creature card
                            playerHandDeck.erase(playerHandDeck.begin() + count);

                            if (item->cardType == "CreatureCard") {
                                playerPlayDeckCreatureRound.push_back(item);
                            }
                            if (item->cardType == "SorceryCard") {
                                playerSorceryDeck.push_back(item);
                                playerPlayDeck.erase(std::remove(playerPlayDeck.begin(), playerPlayDeck.end(), item), playerPlayDeck.end());

                            }

                            break;//break yukarı değilde sadece buraya 1 kez olabilir*****
                        }//colorless cart lazımsa
                        else {//colorless kart gerekli değilse
                            std::cout << "colorless kart gerekli değil " << std::endl;

                            //currentmanadan item.manayı çıkart
                            for (const auto& iter1 : item->manaCost) {

                                int count2 = 0;
                                for (const auto& iter2 : currentManaCost) {

                                    if (iter1 == iter2) {
                                        currentManaCost.erase(currentManaCost.begin() + count2);
                                        break;
                                    }
                                    count2++;
                                }
                            }
                            //colorless cart gerekli değilse
                            //push card to play deck
                            playerPlayDeck.push_back(item);
                            //elden çıkar
                            playerHandDeck.erase(playerHandDeck.begin() + count);

                            if (item->cardType == "CreatureCard") {
                                playerPlayDeckCreatureRound.push_back(item);
                            }
                            if (item->cardType == "SorceryCard") {
                                playerSorceryDeck.push_back(item);
                                playerPlayDeck.erase(std::remove(playerPlayDeck.begin(), playerPlayDeck.end(), item), playerPlayDeck.end());

                            }
                            break;//*
                        }

                        //break;//break yazılabilir**??????????????????????
                    } // land cart dışındaki kartlar için yeterli current manası var mı check et

                    else { //lAND CART DIŞINDA KARTLAR İÇİN YETERLİ MANA YOKSA
                        std::cout << " Not enough mana to play .";
                        break;
                        //playTheCard
                        //order ver ya da
                    }

                } // eğer land kart değilse

                break; //kartı buldun oyniycağını oynadın, çık , zaten her seferinde bir**

            } //if temp == a
            else if (count == playerHandDeck.size() - 1) { //EĞER SON KARTA GELDİYSEN VE HALA KARTI BULAMADIYSAN
                std::cout << " You do not have this card in hand ";
                break;
                //return playTheCard();
            }
            count++;
        }
    }

    //KARTI OYNA
    void playTheCard2() {
        std::string cardName;
        std::cout << " Printing Player " << playerName << "'s hand Cards" << std::endl;//**
        Card::printDeck(playerHandDeck);//*
    goBackHere:
        std::cout << " Pick a card from your hand deck to play, or write 'no' if you do not wish to play any card.";
        std::cin >> cardName;
        std::string a;
        a = cardName;
        int count = 0;
        std::string temp;

        for (const auto& item : playerHandDeck) {
            temp = Card::getName(*item); //hangi karttaysa onun adını al.temp e at

            if (a == "no") {
                std::cout << "  you did not play any card " << std::endl;
                break;
            } //**if else diye break olmadan da yazılabilir.

            //EĞER KART ELİMDE VARSA
            if (temp == a) {

                //EĞER KART LAND KARTSA
                if (item->cardType == "LandCard") {

                    std::cout << " You can not play a land card more than ones in 1 turn " << std::endl;
                    goto goBackHere;

                }
                else { //eğer land kard değilse
                    std::cout << "you choose a non - land card " << std::endl;
                    std::cout << "How many land cards would you like to tap " << std::endl;
                    int howManyToTap;
                    std::cin >> howManyToTap;
                    if (howManyToTap <= playerPlayDeck2.size()) {
                        for (int g = 0; g < howManyToTap; g++) {
                            std::cout << " Choose your " << g + 1 << ". land card to tap from inPlay Deck, that you want to use its manas" << std::endl;
                            std::string landCardToTap;
                            std::cin >> landCardToTap;
                            std::string tempMana;
                            int count3 = 0;

                            // inplay deckte 2 yazılan isimde land card var mı kontrol et
                            //if (std::find(playerPlayDeck2.begin(), playerPlayDeck2.end(),cardName=tempMana) != playerPlayDeck2.end())
                            //{}

                            for (const auto& itemMana : playerPlayDeck2) {
                                tempMana = Card::getName(*itemMana);

                                if (tempMana == landCardToTap && itemMana->cardType == "LandCard") {

                                    //2- varsa onun manasını al ve current manaya pushla
                                    currentManaCost.push_back(itemMana->manaCost[0]);
                                    std::cout << " current mana that you have is " << std::endl;
                                    Card::printManaVector(currentManaCost);
                                    playerPlayDeck2.erase(playerPlayDeck2.begin() + count3);
                                    break;
                                }
                                else if (count3 == playerPlayDeck2.size() - 1) {
                                    std::cout << "you choose a non-land card, or you do not have this card." << std::endl;
                                    g--; //???????
                                    break; //aslında tekrar fonksiyonun başına gitmesi lazım
                                }
                                count3++;
                            }
                            //buraya not found in play2 deck dememiz lazım
                        }
                        //***TAP TAP TAP TAP
                    }

                    else {
                        std::cout << "you do not have that many land cards to tap in your play deck" << std::endl;
                        break;//?????????????????????????????????????????????
                    }

                    //LAND KART DIŞINDA KARTLAR İÇİN CURRENT MANA CHECK ET
                    if (Card::compare(*item, currentManaCost)) {

                        std::cout << " You Can Play the card .";
                        //colorless mana gerekliyse
                        if (item->manaCostC > 0) {
                            //çıkması gereken renkli land cardları bulup 2 loop içinde , çıkar.
                            for (const auto& iter1 : item->manaCost) {
                                int count2 = 0;
                                for (const auto& iter2 : currentManaCost) {

                                    if (iter1 == iter2) {
                                        currentManaCost.erase(currentManaCost.begin() + count2);
                                        break;
                                    }
                                    count2++;
                                }
                            }
                            //çıkması gereken colorless land kart için kartlar seç ve çıkar
                            for (int i = 0; i < item->manaCostC; i++) {
                                std::string temp2;
                                //std::vector<std::string> temp2Vec;
                                std::cout << "which land card you like to play for colorless" << std::endl; //tap fonksi
                                std::cin >> temp2;

                                //temp2Vec.push_back(temp2); //bunun içinde colorless için kullanmak istediği kartların adı var.
                                //***
                                if (temp2 == "Plains") {

                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "W") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "W");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için plains kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found, or you might used it already as color card " << std::endl;
                                        i--;
                                        // break;
                                    }

                                }
                                else if (temp2 == "Forest") {
                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "G") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "G");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için forest kullanıldı" << std::endl;
                                        // break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found, or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }
                                }
                                else if (temp2 == "Island") {
                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "L") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "L");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için ısland kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found  or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }

                                }
                                else if (temp2 == "Mountain") {
                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "R") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "R");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için Mountain kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found  or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }
                                }
                                else if (temp2 == "Swamp") {

                                    if (std::find(currentManaCost.begin(), currentManaCost.end(), "B") != currentManaCost.end()) {
                                        std::cout << "Element found" << std::endl;
                                        //bulduysan sil.
                                        auto it = std::find(currentManaCost.begin(), currentManaCost.end(), "B");
                                        currentManaCost.erase(it);
                                        std::cout << "colorless için swamp kullanıldı" << std::endl;
                                        //break; //????????????
                                    }
                                    else {
                                        std::cout << "Element not found  or you might used it already as color card" << std::endl;
                                        i--;
                                        //break;
                                    }
                                }
                                else {
                                    std::cout << "Element not found" << std::endl;
                                    i--;
                                }
                            }
                            //push creature card to play deck ***aşağıda yap
                            playerPlayDeck.push_back(item);
                            //elden çıkar for creature card
                            playerHandDeck.erase(playerHandDeck.begin() + count);

                            if (item->cardType == "CreatureCard") {
                                playerPlayDeckCreatureRound.push_back(item);
                            }
                            if (item->cardType == "SorceryCard") {
                                playerSorceryDeck.push_back(item);
                                playerPlayDeck.erase(std::remove(playerPlayDeck.begin(), playerPlayDeck.end(), item), playerPlayDeck.end());
                            }

                            break;//break yukarı değilde sadece buraya 1 kez olabilir*****
                        }//colorless cart lazımsa
                        else {//colorless kart gerekli değilse
                            std::cout << "colorless kart gerekli değil " << std::endl;

                            //currentmanadan item.manayı çıkart
                            for (const auto& iter1 : item->manaCost) {

                                int count2 = 0;
                                for (const auto& iter2 : currentManaCost) {

                                    if (iter1 == iter2) {
                                        currentManaCost.erase(currentManaCost.begin() + count2);
                                        break;
                                    }
                                    count2++;
                                }
                            }
                            //colorless cart gerekli değilse
                            //push card to play deck
                            playerPlayDeck.push_back(item);
                            //elden çıkar
                            playerHandDeck.erase(playerHandDeck.begin() + count);

                            if (item->cardType == "CreatureCard") {
                                playerPlayDeckCreatureRound.push_back(item);
                            }
                            if (item->cardType == "SorceryCard") {
                                playerSorceryDeck.push_back(item);
                                playerPlayDeck.erase(std::remove(playerPlayDeck.begin(), playerPlayDeck.end(), item), playerPlayDeck.end());

                            }
                            break;//*
                        }

                        //break;//break yazılabilir**??????????????????????
                    } // land cart dışındaki kartlar için yeterli current manası var mı check et

                    else { //lAND CART DIŞINDA KARTLAR İÇİN YETERLİ MANA YOKSA
                        std::cout << " Not enough mana to play .";
                        break;
                        //playTheCard
                        //order ver ya da
                    }

                } // eğer land kart değilse

                break; //kartı buldun oyniycağını oynadın, çık , zaten her seferinde bir**

            } //if temp == a
            else if (count == playerHandDeck.size() - 1) { //EĞER SON KARTA GELDİYSEN VE HALA KARTI BULAMADIYSAN
                std::cout << " You do not have this card in hand ";
                break;
                //return playTheCard();
            }
            count++;
        }
    }

    void Hand() {
        Card::printDeck(playerHandDeck);
    }
    void PlayDeck() {
        Card::printDeck(playerPlayDeck);
    }

    void PrintCurrentManaVector() {
        Card::printManaVector(currentManaCost);
    }

    friend class Game;
};

class Game :public Player, public Card {

protected:
    Player player_1;
    Player player_2;
    int gameRound = 0;
    int turn = 0;
    bool isGameOver = false;
    //inline static int round=0;

public:

    Game() {
        player_1 = Player();
        player_2 = Player();
        gameRound = 0;
        turn = 0;
        isGameOver = false;
    }

    Game(Player a, Player b) {
        player_1 = a;
        player_2 = b;
        gameRound = 0;
        turn = 0;
        isGameOver = false;
    }

    //oyun biterse ve tekrar initialize etmek istersek
    void init() {

        player_1 = Player();
        player_2 = Player();
        gameRound = 0;
        turn = 0;
        isGameOver = false;

    }

    bool draw(Player& selectedPlayer) {
        std::cout << "You drawed a Card from your Library  " << std::endl;
        return selectedPlayer.drawIfYouCan(); //kütüphanede kart yoksa false döner
    }

    void untap(Player& selectedPlayer) {
        //std::string temp11;
        for (const auto& item11 : selectedPlayer.playerPlayDeck) {
            //temp11 = Card::getName(*item11);

            //untap land cards
            if (getCardType(*item11) == "LandCard") {
                selectedPlayer.playerPlayDeck2.push_back(item11);
            }
        }

        //BASE HP'ye dön- bunu while içinde combattan sonra enmey ve current için yapmak daha mantıklı geldi
        for (const auto& item12 : selectedPlayer.playerPlayDeck) {
            if (getCardType(*item12) == "CreatureCard") {
                //Card::getCardBaseHp(*item12);
                item12->hp = item12->baseHp;
            }
        }

        //UNTAP CREATURE CARDS
        selectedPlayer.playerCombatDeck.clear();

    }

    /* bool play1(Player &selectedPlayer){
         selectedPlayer.Hand();
         char a;
         std::cin>>a;
         return true;
     }
     */

    void play1(Player& selectedPlayer) {

        selectedPlayer.playTheCard();

        //effect
    }

    bool isBattling(Player& selectedPlayer) {
        std::cout << "Would you like to start a combat with the enemy? type yes or no " << std::endl;
        std::string answerForCombat;
        std::cin >> answerForCombat;
        if (answerForCombat == "yes") {
            return true;
        }
        else {
            return false;
        }
    }

    void combat(Player& selectedPlayer) {
        for (const auto& item1122 : selectedPlayer.playerPlayDeck) {

            if (getCardType(*item1122) == "CreatureCard") {
                selectedPlayer.temporaryCreatureDeck.push_back(item1122);
            }
        }

    chooseAgain:
        std::cout << "combat started, pick your creature cards to attack (to tap) " << std::endl;
        std::cout << "How many creature cards you would like to attack with (tap) or write 0 " << std::endl;
        int howManyCreatureToAttack;
        std::cin >> howManyCreatureToAttack;

        if (howManyCreatureToAttack <= 0 || howManyCreatureToAttack > selectedPlayer.playerPlayDeck.size())
        {
            std::cout << " invalid number - passing combat phase without starting it" << std::endl;
        }
        else {
            for (int i = 0; i < howManyCreatureToAttack; i++) {
                std::string tempCreature;
                std::cout << "write your " << i + 1 << ". creature card's name that you want to use in combat" << std::endl;
                std::cin >> tempCreature;
                if (std::find_if(selectedPlayer.temporaryCreatureDeck.begin(), selectedPlayer.temporaryCreatureDeck.end(), [&tempCreature](const auto& item) {
                    return item->name == tempCreature;
                    }) != selectedPlayer.temporaryCreatureDeck.end())
                {
                    auto itCreature = std::find_if(selectedPlayer.temporaryCreatureDeck.begin(), selectedPlayer.temporaryCreatureDeck.end(), [&tempCreature](const auto& item) {
                        return item->name == tempCreature;
                        });
                    if (std::find_if(selectedPlayer.playerPlayDeckCreatureRound.begin(), selectedPlayer.playerPlayDeckCreatureRound.end(), [&tempCreature](const auto& item) {
                        return item->name == tempCreature;

                        }) != selectedPlayer.playerPlayDeckCreatureRound.end())
                    {
                        std::cout << "You can not use " << tempCreature << " in this round, there is summonning sickness please choose another card to attack " << std::endl;
                        goto chooseAgain;
                    }
                    else {
                        std::cout << "You can use " << tempCreature << " in this round " << std::endl;
                        selectedPlayer.playerCombatDeck.push_back(*itCreature);
                        //break;
                    }
                }
                else {
                    std::cout << "You can not use " << tempCreature << " you do not have this card in play or you choose a non creature card please pick again " << std::endl;
                    goto chooseAgain;
                }
            }
        }

        selectedPlayer.temporaryCreatureDeck.clear();
        //std::cout<< "combat ended "<< std::endl;
    }

    void play2(Player& selectedPlayer) {

        if (selectedPlayer.isLandCardPlayed.size() > 0) {
            selectedPlayer.playTheCard2();
        }
        else {
            selectedPlayer.playTheCard();
        }

    }
    void endPhase(Player& selectedPlayer) {
        std::cout << "endphase started " << std::endl;
        selectedPlayer.currentManaCost.clear();
        selectedPlayer.playerPlayDeck2.clear();
        selectedPlayer.playerPlayDeckCreatureRound.clear();
        selectedPlayer.isLandCardPlayed.clear(); //only 1 land card can be played in 1 turn
        selectedPlayer.isEnchantmentEffectsOnes.clear();
        selectedPlayer.isEnchantmentEffectsOnes2.clear();
        std::cout << "endphase  ended " << std::endl;
    }

    void gameLoop() {

        std::cout << "Game has started " << std::endl;

        while (!isGameOver) {

            Player& currentPlayer = turn == 1 ? player_2 : player_1;
            Player& enemyPlayer = turn == 1 ? player_1 : player_2;

            int j;
            if (turn == 0) {
                j = 1;
            }
            else {
                j = 2;
            }

            std::cout << "Round : " << gameRound + 1 << std::endl;
            std::cout << "Turn For Player : " << j << std::endl;
            std::cout << currentPlayer.playerName << " hp is  " << currentPlayer.playerHitPoint << std::endl;
            std::cout << enemyPlayer.playerName << " hp is  " << enemyPlayer.playerHitPoint << std::endl;
            std::cout << "Printing Player " << j << " hand Cards " << std::endl;
            currentPlayer.Hand();

            std::cout << "  " << std::endl;

            //card çekilebilmiş mi fonksiyonu
            bool isDraw = draw(currentPlayer);
            if (!isDraw) {
                isGameOver = true;
                std::cout << "GAME OVER " << std::endl; //for current player
                std::cout << currentPlayer.playerName << " has died" << enemyPlayer.playerName << " has won the game and its hp is " << enemyPlayer.playerHitPoint << std::endl;
                break;
            }

            untap(currentPlayer);
            std::cout << " YOUR PLAY DECK CARDS" << std::endl;
            std::cout << "----------------------" << std::endl;
            currentPlayer.PlayDeck();
            std::cout << " going to the play1 phase " << std::endl;

            //bool isBattling = play1(currentPlayer);
            //eğer battle derse true döndür combat ve play 2 ye git , end turn derse false döndür end phase

            play1(currentPlayer);
            std::cout << "Would you like to play another card? type yes or no " << std::endl;
            std::string answerForPlayingAnotherCard;
            while (std::cin >> answerForPlayingAnotherCard && answerForPlayingAnotherCard == "yes") {
                if (currentPlayer.isLandCardPlayed.size() > 0) {
                    play2(currentPlayer);
                }
                else {
                    play1(currentPlayer);
                }

                std::cout << "Would you like to play another card? type yes or no " << std::endl;//**

            }

            //ENCHANT KARTLARIN HEPSİ PLAY1 DEN SONRA ETKİSİNİ GÖSTERİR
            //Play 1 den sonra bütün echantmant kartları (önceden atılmış olan ve bu el atılan beraber, çünkü hepsi base hpsine geri döndü) özelliklerini etki ettir
            std::string tempEffect;
            for (const auto& itemEffect : currentPlayer.playerPlayDeck) {

                if (itemEffect->cardType == "EnchantmentCard") {
                    currentPlayer.isEnchantmentEffectsOnes.push_back(itemEffect);//play 2 de , burda etkisini gösterenler tekrar etkisini göstermesin diye attık.

                    tempEffect = Card::getName(*itemEffect);

                    //FOR RAGE
                    if (tempEffect == "Rage") {
                        if (!itemEffect->ptr)// if ptr is null , ask for a target
                        {
                        statementToChooseAgain:
                            std::string cardNameToGainTrample;
                            std::cout << " You played a Rage card, choose a target Creature Card from your Deck that you want to give trample ability , or if you do not have a creature card to attach it but you played it, you can simply write no, we will ask you again to pick a creature in next phases" << std::endl;
                            std::cin >> cardNameToGainTrample;

                            if (cardNameToGainTrample == "no") {
                                continue;
                            }
                            else {
                                for (const auto& toCheck : currentPlayer.playerPlayDeck) {

                                    if (cardNameToGainTrample == Card::getName(*toCheck))
                                    {
                                        if (toCheck->cardType == "CreatureCard") {
                                            itemEffect->ptr = toCheck;
                                            Card::setAbility(*toCheck, "Trample");
                                        }//if its a creature card

                                        else {
                                            std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                            goto statementToChooseAgain;

                                        }//if its not a creature card

                                    }//if cardname = toCheck

                                    else {
                                        std::cout << " you picked a card that is not in your hand, please pick again " << std::endl;
                                        goto statementToChooseAgain;
                                    }//if its not in hand

                                }//for toCheck döngüsü

                            }

                        }//end of if ptr is null

                        else if (itemEffect->ptr) {

                            //ptr null değilse iki durum var 1.si içinde tuttuğu creature is alive 2.is dead bunu da play destesinde aratarak bulabiliri z
                            if (itemEffect->ptr->hp <= 0) {
                                Card::setAbility(*itemEffect->ptr, "Null");
                                itemEffect->ptr = NULL;
                                currentPlayer.playerDiscardDeck.push_back(itemEffect);
                                currentPlayer.playerPlayDeck.erase(std::remove(currentPlayer.playerPlayDeck.begin(), currentPlayer.playerPlayDeck.end(), itemEffect), currentPlayer.playerPlayDeck.end());

                            }

                        }

                        //continue;

                    }//end of if rage


                        //FOR SLOW
                    else if (tempEffect == "Slow") {
                        if (!itemEffect->ptr)// if ptr is null , ask for a target
                        {
                        statementToChooseAgain2:
                            std::string cardNameToLoseFirstStrike;
                            std::cout << " You played a Slow card, choose a target Creature Card from enemy that you want to remove first strike  , or if you do not find a creature card to attach it but you played it, you can simply write no, we will ask you again to pick a creature in next phases" << std::endl;
                            std::cin >> cardNameToLoseFirstStrike;

                            if (cardNameToLoseFirstStrike == "no") {
                                continue;
                            }
                            else {
                                for (const auto& toCheck : enemyPlayer.playerPlayDeck) {

                                    if (cardNameToLoseFirstStrike == Card::getName(*toCheck))
                                    {
                                        if (toCheck->cardType == "CreatureCard") {

                                            if (toCheck->ability == "FirstStrike") {
                                                itemEffect->ptr = toCheck;
                                                Card::setAbility(*toCheck, "Null");
                                            }

                                            else {
                                                std::cout << "You did not pick a card that has first strike ability, choose another card " << std::endl;
                                                goto statementToChooseAgain2;
                                            }
                                        }// if creature card
                                        else {
                                            std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                            goto statementToChooseAgain2;

                                        }//if its not a creature card

                                    }//if cardname = toCheck

                                    else {
                                        std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                        goto statementToChooseAgain2;
                                    }//if its not in hand

                                }//for toCheck döngüsü

                            }

                        }//end of if ptr is null

                        else if (itemEffect->ptr) {

                            //ptr null değilse iki durum var 1.si içinde tuttuğu creature is alive 2.is dead bunu da play destesinde aratarak bulabiliri z
                            if (itemEffect->ptr->hp <= 0) {
                                Card::setAbility(*itemEffect->ptr, "FirstStrike");
                                itemEffect->ptr = NULL;
                                currentPlayer.playerDiscardDeck.push_back(itemEffect);
                                currentPlayer.playerPlayDeck.erase(std::remove(currentPlayer.playerPlayDeck.begin(), currentPlayer.playerPlayDeck.end(), itemEffect), currentPlayer.playerPlayDeck.end());

                            }

                        }

                        //continue;

                    }//end of if slow


                        //FOR RESTRAIN
                    else if (tempEffect == "Restrain") {

                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {

                            if (toCheck->cardColor == "GREEN")
                            {
                                if (toCheck->cardType == "CreatureCard") {
                                    Card::setAbility(*toCheck, "Null");
                                }
                            }
                        }//if cardname = toCheck
                    }//end of restrain

                        //FOR UNHOLYWAR
                    else if (tempEffect == "UnholyWar") {
                        for (const auto& toCheck : currentPlayer.playerPlayDeck) {
                            if (toCheck->cardColor == "BLACK") {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->attackPower = toCheck->attackPower + 2;
                                }
                            }
                        }
                    }//end of holywar

                        //FOR HOLYWAR
                    else if (tempEffect == "HolyWar") {
                        for (const auto& toCheck : currentPlayer.playerPlayDeck) {
                            if (toCheck->cardColor == "WHITE") {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->attackPower = toCheck->attackPower + 1;
                                    toCheck->hp = toCheck->hp + 1;
                                }
                            }
                        }
                    }//end of holywar

                        //FOR HOLYLIGHT
                    else if (tempEffect == "HolyLight") {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (toCheck->cardColor == "WHITE") {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->attackPower = toCheck->attackPower - 1;
                                    toCheck->hp = toCheck->hp - 1;
                                    if (toCheck->hp <= 0) {
                                        std::cout << toCheck->name << " is dead " << std::endl;
                                        enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                        enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    }
                                }
                            }
                        }
                    }//end of holylight



                }


            }



            std::string tempSorcery;
            for (const auto& itemSorcery : currentPlayer.playerSorceryDeck) {
                tempSorcery = Card::getName(*itemSorcery);
                if (tempSorcery == "Disenchant") {
                statementToChooseAgain33:
                    std::string cardNameToDestroyTargetEnch;
                    std::cout << " You played a Disenchant card, choose a target Enchantment Card from enemy that you want to remove or you can write no and you send your sorcery card to graveyard without playing it, (you can not take it back to your hand)  " << std::endl;
                    std::cin >> cardNameToDestroyTargetEnch;
                    if (cardNameToDestroyTargetEnch == "no") {
                        continue;
                    }

                    else {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (cardNameToDestroyTargetEnch == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "EnchantmentCard") {
                                    enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                    enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    std::cout << " you killed an enchantment card " << cardNameToDestroyTargetEnch << std::endl;
                                }// if creature card
                                else {
                                    std::cout << " you did not pick an Enchantment card please pick an Enchantment card " << std::endl;
                                    goto statementToChooseAgain33;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain33;
                            }//if its not in hand

                        }//for toCheck döngüsü
                    }

                }//end of Disenchant

                else if (tempSorcery == "LightningBolt") {
                statementToChooseAgain36:
                    std::string damageToCardOrPlayer;
                    std::cout << " You played a lightningbolt card, choose a target creature Card from enemy that you want to remove or you can write player if you wish to attack your enemy directly " << std::endl;
                    std::cin >> damageToCardOrPlayer;
                    if (damageToCardOrPlayer == "player") {
                        enemyPlayer.playerHitPoint = enemyPlayer.playerHitPoint - 2;
                        if (enemyPlayer.playerHitPoint <= 0) {
                            isGameOver = true;
                            std::cout << " enemy is dead " << std::endl;
                            break;
                        }
                    }

                    else {
                        std::string enemyCreature;
                        std::cout << "select a creature card name from your enemy's deck" << std::endl;
                        std::cin >> enemyCreature;
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (damageToCardOrPlayer == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->hp = toCheck->hp - 2;
                                    if (toCheck->hp <= 0) {
                                        enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                        enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                        std::cout << " you killed an creature card " << damageToCardOrPlayer << std::endl;
                                    }

                                }// if creature card
                                else {
                                    std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                    goto statementToChooseAgain36;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain36;
                            }//if its not in hand
                        }//for toCheck döngüsü
                    }
                }//end of lightning bold

                else if (tempSorcery == "Flood") {

                statementToChooseAgain34:
                    std::string cardNameToDestroyTargetLand;
                    std::cout << " You played a Flood card, choose a target land Card from enemy that you want to remove or you can write no and you send your sorcery card to graveyard without playing it, (you can not take it back to your hand)  " << std::endl;
                    std::cin >> cardNameToDestroyTargetLand;
                    if (cardNameToDestroyTargetLand == "no") {
                        continue;
                    }

                    else {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (cardNameToDestroyTargetLand == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "LandCard") {
                                    enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                    enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    std::cout << " you killed an land card " << cardNameToDestroyTargetLand << std::endl;
                                }// if creature card
                                else {
                                    std::cout << " you did not pick a land card please pick a land card " << std::endl;
                                    goto statementToChooseAgain34;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain34;
                            }//if its not in hand

                        }//for toCheck döngüsü
                    }

                }//end of flood

                else if (tempSorcery == "Plague") {
                    std::cout << " You played a plague card " << std::endl;
                    for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                        if (toCheck->cardType == "CreatureCard") {
                            toCheck->hp = toCheck->hp - 1;
                            if (toCheck->hp <= 0) {
                                std::cout << toCheck->name << " is dead" << std::endl;
                                enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                enemyPlayer.playerDiscardDeck.push_back(toCheck);
                            }
                        }

                    }

                }//end of plague
                else if (tempSorcery == "Terror") {
                statementToChooseAgain35:
                    std::string cardNameToDestroyTargetCre;
                    std::cout << " You played a Terror card, choose a target creature Card from enemy that you want to remove or you can write no and you send your sorcery card to graveyard without playing it, (you can not take it back to your hand)  " << std::endl;
                    std::cin >> cardNameToDestroyTargetCre;
                    if (cardNameToDestroyTargetCre == "no") {
                        continue;
                    }

                    else {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (cardNameToDestroyTargetCre == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "CreatureCard") {
                                    enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                    enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    std::cout << " you killed an creature card " << cardNameToDestroyTargetCre << std::endl;
                                }// if creature card
                                else {
                                    std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                    goto statementToChooseAgain35;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain35;
                            }//if its not in hand
                        }//for toCheck döngüsü
                    }
                }//end of terror

                else if (tempSorcery == "Reanimate") {
                    std::cout << " you play a reanimate card, you can choose a card from your discard deck, please write the name of the card that you want to take" << std::endl;
                    if (currentPlayer.playerDiscardDeck.size() <= 0) {
                        std::cout << " you do not have any card in discard deck, you lose the card and effect " << std::endl;
                        break;//?????????
                    }
                    else {
                        Card::printDeckDiscard(currentPlayer.playerDiscardDeck);
                        std::string choosenCardToTake;
                        std::cin >> choosenCardToTake;
                        for (const auto& toCheck : currentPlayer.playerDiscardDeck) {
                            if (choosenCardToTake == Card::getName(*toCheck))
                            {
                                if (choosenCardToTake == "AngryBear" || choosenCardToTake == "Werewolf") {
                                    Card::setAbility(*toCheck, "Trample");
                                }
                                toCheck->hp = toCheck->baseHp;
                                currentPlayer.playerDiscardDeck.erase(std::remove(currentPlayer.playerDiscardDeck.begin(), currentPlayer.playerDiscardDeck.end(), toCheck), currentPlayer.playerDiscardDeck.end());
                                currentPlayer.playerHandDeck.push_back(toCheck);
                            }
                        }
                    }
                }//end of reanimate
            }//for auto itemsorcery in playerSorceryDeck


            currentPlayer.playerDiscardDeck.insert(std::end(currentPlayer.playerDiscardDeck), std::begin(currentPlayer.playerSorceryDeck), std::end(currentPlayer.playerSorceryDeck));

            currentPlayer.playerSorceryDeck.clear();



            std::cout << " you played your card(s), going to the next phase " << std::endl;


            //* currentPlayer.playerHandDeck;

            bool isCombat = isBattling(currentPlayer);

            if (isCombat) {
                std::cout << " Combat has started " << std::endl;
                Card::printDeck(currentPlayer.playerPlayDeck);
                combat(currentPlayer);
                if (currentPlayer.playerCombatDeck.size() <= 0) {
                    std::cout << " Attacker did not attack with any card, no need to defend" << std::endl;
                }
                else {
                    std::cout << enemyPlayer.playerName << " your enemy is attacking you with these cards " << std::endl;
                    //**
                    for (int i = 0; i < currentPlayer.playerCombatDeck.size(); i++) {
                        std::cout << i + 1 << ". creature that attacks ";
                        Card::printDeckPower(currentPlayer.playerCombatDeck); //burda cartların attackleri ve hp leri çıksın***
                    }
                    //***

                    std::cout << enemyPlayer.playerName << " would you like to defend type yes or no " << std::endl;
                    std::string yesOrNoForDefend;
                    std::cin >> yesOrNoForDefend;
                    if (yesOrNoForDefend == "yes")
                    {
                        std::cout << " You should write names of the defending creatures that you select, in the same order with your enemy's attack cards (they will match accordingly)" << std::endl;

                        for (int i = 0; i < currentPlayer.playerCombatDeck.size(); i++) {
                        chooseDefandCard: //goto keyword'ü için
                            std::string tempCreatureDefender;
                            std::cout << "write your " << i + 1 << ". creature card's name that you want to defend or if you want to pass write no" << std::endl;
                            std::cin >> tempCreatureDefender;

                            //eğer sıradaki attack kard için savunma seçmezse, kartın attacki kendi hpsinden direkt
                            if (tempCreatureDefender == "no") {
                                int attackPowerForAttackingCreature;
                                attackPowerForAttackingCreature = currentPlayer.playerCombatDeck.at(i)->attackPower;
                                enemyPlayer.playerHitPoint = enemyPlayer.playerHitPoint - attackPowerForAttackingCreature;
                                if (enemyPlayer.playerHitPoint <= 0) {
                                    std::cout << enemyPlayer.playerName << " is dead due to below 0 hp " << std::endl;
                                    std::cout << currentPlayer.playerName << " has win the game and its hp is" << currentPlayer.playerHitPoint << std::endl;
                                    isGameOver = true;
                                }
                                i++;
                                goto chooseDefandCard;
                            }
                            else {
                                int count571 = 0;
                                for (const auto& tempCreatureDefender2 : enemyPlayer.playerPlayDeck) {
                                    //enemynin elindeki seçtiği card destede var mı
                                    if (getName(*tempCreatureDefender2) == tempCreatureDefender) {
                                        //enemynin elindeki seçtiği card türü creature mı
                                        if (getCardType(*tempCreatureDefender2) == "CreatureCard") {
                                            //Enemy yani  defender'ın oynadığı creature card tapped mi değil mi kontrol et
                                            if (std::find_if(enemyPlayer.playerCombatDeck.begin(), enemyPlayer.playerCombatDeck.end(), [&tempCreatureDefender](const auto& item) {
                                                return item->name == tempCreatureDefender;
                                                }) != enemyPlayer.playerCombatDeck.end())
                                            {
                                                std::cout << "You can not use " << tempCreatureDefender << " in this round, it is still tapped, please choose another card to attack " << std::endl;
                                                goto chooseDefandCard;//iki loop üste break edebiilir mi? i ile player combat deck gezdiği loopa gitsin istiyoruz.
                                            }
                                            else { //tap olmama durumunda

                                                //defender ın oynadığı kart o el başka bir karta savunma için kullanılmış mı kontrol et.

                                                if (std::find_if(enemyPlayer.playerDefendDeck.begin(), enemyPlayer.playerDefendDeck.end(), [&tempCreatureDefender](const auto& item) {
                                                    return item->name == tempCreatureDefender;

                                                    }) != enemyPlayer.playerDefendDeck.end())
                                                {
                                                    std::cout << "you defend yourself with this card only 1 time in this combat, please choose another card" << std::endl;

                                                    goto chooseDefandCard;
                                                }
                                                else {
                                                    std::cout << "You can use " << tempCreatureDefender << " in this round " << std::endl;
                                                    enemyPlayer.playerDefendDeck.push_back(tempCreatureDefender2);//aynı kartla iki kez savunma yapmaması için check etmeye yarayan deck

                                                    //If the attacking creature has TRAMPLE ability a
                                                    if (currentPlayer.playerCombatDeck.at(i)->ability == "Trample") {
                                                        //ilk önce attack power - hp ayarları
                                                        tempCreatureDefender2->hp = tempCreatureDefender2->hp - currentPlayer.playerCombatDeck.at(i)->attackPower;

                                                        currentPlayer.playerCombatDeck.at(i)->hp = currentPlayer.playerCombatDeck.at(i)->hp - tempCreatureDefender2->attackPower;
                                                        //find excess attackpower
                                                        int excessAttackPower = 0;
                                                        excessAttackPower = currentPlayer.playerCombatDeck.at(i)->attackPower - tempCreatureDefender2->hp;
                                                        if (excessAttackPower > 0) {
                                                            enemyPlayer.playerHitPoint = enemyPlayer.playerHitPoint - excessAttackPower;
                                                            std::cout << currentPlayer.playerName << " you used your trample ability, defenders new Hp is " << enemyPlayer.playerHitPoint << std::endl;
                                                        }
                                                        else {
                                                            std::cout << currentPlayer.playerName << " you couldn't use your trample ability because there is no excess attack power" << std::endl;
                                                        }
                                                    }
                                                    //If the attacking creature has FIRST STRIKE ability - b
                                                    else if (currentPlayer.playerCombatDeck.at(i)->ability == "FirstStrike")
                                                    {
                                                        //b-i
                                                        if (tempCreatureDefender2->ability == "FirstStrike") {

                                                            //normal prosedür
                                                            tempCreatureDefender2->hp = tempCreatureDefender2->hp - currentPlayer.playerCombatDeck.at(i)->attackPower;
                                                            currentPlayer.playerCombatDeck.at(i)->hp = currentPlayer.playerCombatDeck.at(i)->hp - tempCreatureDefender2->attackPower;
                                                        }
                                                        //b-ii
                                                        else {
                                                            //first attacker saldırır sonra defender ın hpsi kalıp kalmadığına bakılır eğer hpsi 0 dan az ise saldıramadan ölür.
                                                            tempCreatureDefender2->hp = tempCreatureDefender2->hp - currentPlayer.playerCombatDeck.at(i)->attackPower;
                                                            if (tempCreatureDefender2->hp <= 0) {
                                                                std::cout << enemyPlayer.playerName << " your defend card had an attack from a card that has first strike and you died before you attack " << std::endl;
                                                            }
                                                            else {
                                                                std::cout << enemyPlayer.playerName << " your defend card had an attack from a card that has first strike but your card still has hp so you attacked back " << std::endl;
                                                                currentPlayer.playerCombatDeck.at(i)->hp = currentPlayer.playerCombatDeck.at(i)->hp - tempCreatureDefender2->attackPower;
                                                            }
                                                        }
                                                    }
                                                    //If the attacking creature has no FIRST STRIKE ability no trample ability - c
                                                    else {
                                                        //if the defender has first strike c - i
                                                        if (tempCreatureDefender2->ability == "FirstStrike") {
                                                            //ilk defender saldırır sonra attackerın kalan hpsine göre attacker saldıramadan ölür veya canı kalmıştır ve saldırır
                                                            currentPlayer.playerCombatDeck.at(i)->hp = currentPlayer.playerCombatDeck.at(i)->hp - tempCreatureDefender2->attackPower;

                                                            if (currentPlayer.playerCombatDeck.at(i)->hp <= 0) {
                                                                std::cout << currentPlayer.playerName << " your attack card had an defense from a card that has first strike and you died before you attack " << std::endl;
                                                            }

                                                            else {
                                                                std::cout << currentPlayer.playerName << " your attack card had an defend from a card that has first strike but your card still has hp so you attacked back " << std::endl;
                                                                tempCreatureDefender2->hp = tempCreatureDefender2->hp - currentPlayer.playerCombatDeck.at(i)->attackPower;
                                                            }

                                                        }
                                                        //if the defender also do not have any ability c - ii
                                                        else {
                                                            tempCreatureDefender2->hp = tempCreatureDefender2->hp - currentPlayer.playerCombatDeck.at(i)->attackPower;

                                                            currentPlayer.playerCombatDeck.at(i)->hp = currentPlayer.playerCombatDeck.at(i)->hp - tempCreatureDefender2->attackPower;
                                                        }

                                                    }

                                                    if (tempCreatureDefender2->hp <= 0) {

                                                        enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), tempCreatureDefender2), enemyPlayer.playerPlayDeck.end());

                                                        enemyPlayer.playerDiscardDeck.push_back(tempCreatureDefender2);
                                                        std::cout << tempCreatureDefender << " card is dead, goes to graveyard" << std::endl;
                                                    }

                                                    if (currentPlayer.playerCombatDeck.at(i)->hp <= 0) {
                                                        currentPlayer.playerPlayDeck.erase(currentPlayer.playerPlayDeck.begin() + i);
                                                        //??????????????? i mi i+1 mi
                                                        currentPlayer.playerDiscardDeck.push_back(currentPlayer.playerCombatDeck.at(i));
                                                        std::cout << currentPlayer.playerCombatDeck.at(i)->name << " card is dead, goes to graveyard" << std::endl;
                                                    }
                                                    i++;
                                                    goto chooseDefandCard; //burada i++yapmamız lazım mı?

                                                }//else - you can use this card to defend in this round

                                            }//tap olmama durumu
                                            break; // ******************* 2 defa aynı kartı kullanmama olayı için silindi

                                        } //if creature card
                                            //else (adı creature card değilse) içinde mutlaka break olmalı
                                        else {
                                            std::cout << "You can not use " << tempCreatureDefender << " this is not a creature card" << std::endl;
                                            i--;
                                            break;
                                        }
                                        break; //???????????????
                                    }
                                    //eğer enemynin seçtiği kart destede yoksa
                                    else if (count571 == enemyPlayer.playerPlayDeck.size() - 1)
                                    {
                                        std::cout << "You can not use " << tempCreatureDefender << " you do not have this card in play" << std::endl;
                                        i--;
                                        break;
                                    }
                                    count571++;

                                }//enmy player deck i dönen for loop
                            }//else eğer o karta cevap vermeyi seçtiyse
                        }//player combat deck size kadar dönen for

                    }//yes or no = yes in bittiği yer

                    else if (yesOrNoForDefend == "no") {
                        std::cout << " you did not defend yourself , your hp will decrease " << std::endl;
                        int totalAttackPower = 0;
                        for (const auto& item388 : currentPlayer.playerCombatDeck) {
                            totalAttackPower = totalAttackPower + item388->attackPower;
                        }
                        enemyPlayer.playerHitPoint = enemyPlayer.playerHitPoint - totalAttackPower;
                        if (enemyPlayer.playerHitPoint <= 0) {
                            isGameOver = true;
                            std::cout << "GAME OVER " << std::endl; //for current player
                            std::cout << currentPlayer.playerName << " has won, hp is " << currentPlayer.playerHitPoint << std::endl;
                            break;
                        }
                    }
                    else
                    {
                        std::cout << " you did not write a proper answer , you can not defend yourself " << std::endl;
                        int totalAttackPower = 0;
                        for (const auto& item388 : currentPlayer.playerCombatDeck) {
                            totalAttackPower = totalAttackPower + item388->attackPower;
                        }
                        enemyPlayer.playerHitPoint = enemyPlayer.playerHitPoint - totalAttackPower;
                        if (enemyPlayer.playerHitPoint <= 0) {
                            isGameOver = true;
                            std::cout << "GAME OVER " << std::endl; //for current player
                            std::cout << currentPlayer.playerName << " has won, hp is " << currentPlayer.playerHitPoint << std::endl;
                            break;
                        }
                    }
                    //***
                    enemyPlayer.playerDefendDeck.clear(); //defans edenin tap durumu olmadığı için burada temizledik.

                    std::cout << "combat phase is ending , going to the next play2 phase " << std::endl;

                }
            }

            play2(currentPlayer);
            std::cout << "Would you like to play another card? type yes or no " << std::endl;
            std::string answerForPlayingAnotherCard2;
            while (std::cin >> answerForPlayingAnotherCard2 && answerForPlayingAnotherCard2 == "yes") {
                play2(currentPlayer);
                std::cout << "Would you like to play another card? type yes or no " << std::endl;//**
            }

            for (const auto& iter1 : currentPlayer.isEnchantmentEffectsOnes) {
                int count2 = 0;
                for (const auto& iter2 : currentPlayer.playerPlayDeck) {

                    if (Card::getName(*iter1) != Card::getName(*iter2)) {
                        currentPlayer.isEnchantmentEffectsOnes2.push_back(iter2);
                        break;
                    }
                    count2++;
                }
            }




            //ENCHANT KARTLARIN SADECE IKINCI PLAYDE OYUNA ATILANLARI ETKİ EDER ÇÜNKÜ HER TUR ENCHANTMEN KART 1 KEZ ETKİSİNİ GÖSTERMELİ
            std::string tempEffect2;
            for (const auto& itemEffect : currentPlayer.isEnchantmentEffectsOnes2) {

                if (itemEffect->cardType == "EnchantmentCard") {
                    currentPlayer.isEnchantmentEffectsOnes.push_back(itemEffect);//play 2 de , burda etkisini gösterenler tekrar etkisini göstermesin diye attık.

                    tempEffect2 = Card::getName(*itemEffect);

                    //FOR RAGE
                    if (tempEffect2 == "Rage") {
                        if (!itemEffect->ptr)// if ptr is null , ask for a target
                        {
                        statementToChooseAgain11:
                            std::string cardNameToGainTrample;
                            std::cout << " You played a Rage card, choose a target Creature Card from your Deck that you want to give trample ability , or if you do not have a creature card to attach it but you played it, you can simply write no, we will ask you again to pick a creature in next phases" << std::endl;
                            std::cin >> cardNameToGainTrample;

                            if (cardNameToGainTrample == "no") {
                                continue;
                            }
                            else {
                                for (const auto& toCheck : currentPlayer.playerPlayDeck) {

                                    if (cardNameToGainTrample == Card::getName(*toCheck))
                                    {
                                        if (toCheck->cardType == "CreatureCard") {
                                            itemEffect->ptr = toCheck;
                                            Card::setAbility(*toCheck, "Trample");
                                        }//if its a creature card

                                        else {
                                            std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                            goto statementToChooseAgain11;

                                        }//if its not a creature card

                                    }//if cardname = toCheck

                                    else {
                                        std::cout << " you picked a card that is not in your hand, please pick again " << std::endl;
                                        goto statementToChooseAgain11;
                                    }//if its not in hand

                                }//for toCheck döngüsü

                            }

                        }//end of if ptr is null

                        else if (itemEffect->ptr) {

                            //ptr null değilse iki durum var 1.si içinde tuttuğu creature is alive 2.is dead bunu da play destesinde aratarak bulabiliri z
                            if (itemEffect->ptr->hp <= 0) {
                                Card::setAbility(*itemEffect->ptr, "Null");
                                itemEffect->ptr = NULL;
                                currentPlayer.playerDiscardDeck.push_back(itemEffect);
                                currentPlayer.playerPlayDeck.erase(std::remove(currentPlayer.playerPlayDeck.begin(), currentPlayer.playerPlayDeck.end(), itemEffect), currentPlayer.playerPlayDeck.end());

                            }

                        }

                        //continue;

                    }//end of if rage


                        //FOR SLOW
                    else if (tempEffect2 == "Slow") {
                        if (!itemEffect->ptr)// if ptr is null , ask for a target
                        {
                        statementToChooseAgain22:
                            std::string cardNameToLoseFirstStrike;
                            std::cout << " You played a Slow card, choose a target Creature Card from enemy that you want to remove first strike  , or if you do not find a creature card to attach it but you played it, you can simply write no, we will ask you again to pick a creature in next phases" << std::endl;
                            std::cin >> cardNameToLoseFirstStrike;

                            if (cardNameToLoseFirstStrike == "no") {
                                continue;
                            }
                            else {
                                for (const auto& toCheck : enemyPlayer.playerPlayDeck) {

                                    if (cardNameToLoseFirstStrike == Card::getName(*toCheck))
                                    {
                                        if (toCheck->cardType == "CreatureCard") {

                                            if (toCheck->ability == "FirstStrike") {
                                                itemEffect->ptr = toCheck;
                                                Card::setAbility(*toCheck, "Null");
                                            }

                                            else {
                                                std::cout << "You did not pick a card that has first strike ability, choose another card " << std::endl;
                                                goto statementToChooseAgain22;
                                            }
                                        }// if creature card
                                        else {
                                            std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                            goto statementToChooseAgain22;

                                        }//if its not a creature card

                                    }//if cardname = toCheck

                                    else {
                                        std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                        goto statementToChooseAgain22;
                                    }//if its not in hand

                                }//for toCheck döngüsü

                            }

                        }//end of if ptr is null

                        else if (itemEffect->ptr) {

                            //ptr null değilse iki durum var 1.si içinde tuttuğu creature is alive 2.is dead bunu da play destesinde aratarak bulabiliri z
                            if (itemEffect->ptr->hp <= 0) {
                                Card::setAbility(*itemEffect->ptr, "FirstStrike");
                                itemEffect->ptr = NULL;
                                currentPlayer.playerDiscardDeck.push_back(itemEffect);
                                currentPlayer.playerPlayDeck.erase(std::remove(currentPlayer.playerPlayDeck.begin(), currentPlayer.playerPlayDeck.end(), itemEffect), currentPlayer.playerPlayDeck.end());

                            }

                        }

                        //continue;

                    }//end of if slow


                        //FOR RESTRAIN
                    else if (tempEffect2 == "Restrain") {

                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {

                            if (toCheck->cardColor == "GREEN")
                            {
                                if (toCheck->cardType == "CreatureCard") {
                                    Card::setAbility(*toCheck, "Null");
                                }
                            }
                        }//if cardname = toCheck
                    }//end of restrain

                        //FOR UNHOLYWAR
                    else if (tempEffect2 == "UnholyWar") {
                        for (const auto& toCheck : currentPlayer.playerPlayDeck) {
                            if (toCheck->cardColor == "BLACK") {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->attackPower = toCheck->attackPower + 2;
                                }
                            }
                        }
                    }//end of holywar

                        //FOR HOLYWAR
                    else if (tempEffect2 == "HolyWar") {
                        for (const auto& toCheck : currentPlayer.playerPlayDeck) {
                            if (toCheck->cardColor == "WHITE") {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->attackPower = toCheck->attackPower + 1;
                                    toCheck->hp = toCheck->hp + 1;
                                }
                            }
                        }
                    }//end of holywar

                        //FOR HOLYLIGHT
                    else if (tempEffect2 == "HolyLight") {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (toCheck->cardColor == "WHITE") {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->attackPower = toCheck->attackPower - 1;
                                    toCheck->hp = toCheck->hp - 1;
                                }
                            }
                        }
                    }//end of holylight



                }


            }

            std::string tempSorcery2;
            for (const auto& itemSorcery : currentPlayer.playerSorceryDeck) {
                tempSorcery2 = Card::getName(*itemSorcery);
                if (tempSorcery2 == "Disenchant") {
                statementToChooseAgain43:
                    std::string cardNameToDestroyTargetEnch;
                    std::cout << " You played a Disenchant card, choose a target Enchantment Card from enemy that you want to remove or you can write no and you send your sorcery card to graveyard without playing it, (you can not take it back to your hand)  " << std::endl;
                    std::cin >> cardNameToDestroyTargetEnch;
                    if (cardNameToDestroyTargetEnch == "no") {
                        continue;
                    }

                    else {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (cardNameToDestroyTargetEnch == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "EnchantmentCard") {
                                    enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                    enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    std::cout << " you killed an enchantment card " << cardNameToDestroyTargetEnch << std::endl;
                                }// if creature card
                                else {
                                    std::cout << " you did not pick an Enchantment card please pick an Enchantment card " << std::endl;
                                    goto statementToChooseAgain43;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain43;
                            }//if its not in hand

                        }//for toCheck döngüsü
                    }

                }//end of Disenchant

                else if (tempSorcery2 == "LightningBolt") {
                statementToChooseAgain46:
                    std::string damageToCardOrPlayer;
                    std::cout << " You played a lightningbolt card, choose a target creature Card from enemy that you want to remove or you can write player if you wish to attack your enemy directly " << std::endl;
                    std::cin >> damageToCardOrPlayer;
                    if (damageToCardOrPlayer == "player") {
                        enemyPlayer.playerHitPoint = enemyPlayer.playerHitPoint - 2;
                        if (enemyPlayer.playerHitPoint <= 0) {
                            isGameOver = true;
                            std::cout << " enemy is dead " << std::endl;
                            std::cout << currentPlayer.playerName << " has won " << std::endl;
                            break;
                        }
                    }

                    else {
                        std::string enemyCreature;
                        std::cout << "select a creature card name from your enemy's deck" << std::endl;
                        std::cin >> enemyCreature;
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (damageToCardOrPlayer == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "CreatureCard") {
                                    toCheck->hp = toCheck->hp - 2;
                                    if (toCheck->hp <= 0) {
                                        enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                        enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                        std::cout << " you killed an creature card " << damageToCardOrPlayer << std::endl;
                                    }

                                }// if creature card
                                else {
                                    std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                    goto statementToChooseAgain46;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain46;
                            }//if its not in hand
                        }//for toCheck döngüsü
                    }
                }//end of lightning bold

                else if (tempSorcery2 == "Flood") {

                statementToChooseAgain44:
                    std::string cardNameToDestroyTargetLand;
                    std::cout << " You played a Flood card, choose a target land Card from enemy that you want to remove or you can write no and you send your sorcery card to graveyard without playing it, (you can not take it back to your hand)  " << std::endl;
                    std::cin >> cardNameToDestroyTargetLand;
                    if (cardNameToDestroyTargetLand == "no") {
                        continue;
                    }

                    else {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (cardNameToDestroyTargetLand == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "LandCard") {
                                    enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                    enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    std::cout << " you killed an land card " << cardNameToDestroyTargetLand << std::endl;
                                }// if creature card
                                else {
                                    std::cout << " you did not pick a land card please pick a land card " << std::endl;
                                    goto statementToChooseAgain44;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain44;
                            }//if its not in hand

                        }//for toCheck döngüsü
                    }

                }//end of flood

                else if (tempSorcery2 == "Plague") {
                    std::cout << " You played a plague card " << std::endl;
                    for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                        if (toCheck->cardType == "CreatureCard") {
                            toCheck->hp = toCheck->hp - 1;
                            if (toCheck->hp <= 0) {
                                std::cout << toCheck->name << " is dead" << std::endl;
                                enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                enemyPlayer.playerDiscardDeck.push_back(toCheck);
                            }
                        }

                    }

                }//end of plague
                else if (tempSorcery2 == "Terror") {
                statementToChooseAgain45:
                    std::string cardNameToDestroyTargetCre;
                    std::cout << " You played a Terror card, choose a target creature Card from enemy that you want to remove or you can write no and you send your sorcery card to graveyard without playing it, (you can not take it back to your hand)  " << std::endl;
                    std::cin >> cardNameToDestroyTargetCre;
                    if (cardNameToDestroyTargetCre == "no") {
                        continue;
                    }

                    else {
                        for (const auto& toCheck : enemyPlayer.playerPlayDeck) {
                            if (cardNameToDestroyTargetCre == Card::getName(*toCheck))
                            {
                                if (toCheck->cardType == "CreatureCard") {
                                    enemyPlayer.playerPlayDeck.erase(std::remove(enemyPlayer.playerPlayDeck.begin(), enemyPlayer.playerPlayDeck.end(), toCheck), enemyPlayer.playerPlayDeck.end());
                                    enemyPlayer.playerDiscardDeck.push_back(toCheck);
                                    std::cout << " you killed an creature card " << cardNameToDestroyTargetCre << std::endl;
                                }// if creature card
                                else {
                                    std::cout << " you did not pick a creature card please pick a creature card " << std::endl;
                                    goto statementToChooseAgain45;
                                }//if its not a creature card

                            }//if cardname = toCheck

                            else {
                                std::cout << " you picked a card that is not in your enemy's hand, please pick again " << std::endl;
                                goto statementToChooseAgain45;
                            }//if its not in hand
                        }//for toCheck döngüsü
                    }
                }//end of terror

                else if (tempSorcery2 == "Reanimate") {
                    std::cout << " you play a reanimate card, you can choose a card from your discard deck, pelase write the name of the card that you want to take" << std::endl;
                    Card::printDeckDiscard(currentPlayer.playerDiscardDeck);
                    std::string choosenCardToTake;
                    std::cin >> choosenCardToTake;
                    for (const auto& toCheck : currentPlayer.playerDiscardDeck) {
                        if (choosenCardToTake == Card::getName(*toCheck))
                        {
                            if (choosenCardToTake == "AngryBear" || choosenCardToTake == "Werewolf") {
                                Card::setAbility(*toCheck, "Trample");
                            }
                            toCheck->hp = toCheck->baseHp;
                            currentPlayer.playerDiscardDeck.erase(std::remove(currentPlayer.playerDiscardDeck.begin(), currentPlayer.playerDiscardDeck.end(), toCheck), currentPlayer.playerDiscardDeck.end());
                            currentPlayer.playerHandDeck.push_back(toCheck);
                        }
                    }
                }//end of reanimate
            }//for auto itemsorcery in playerSorceryDeck

            currentPlayer.playerDiscardDeck.insert(std::end(currentPlayer.playerDiscardDeck), std::begin(currentPlayer.playerSorceryDeck), std::end(currentPlayer.playerSorceryDeck));

            currentPlayer.playerSorceryDeck.clear();

            endPhase(currentPlayer);
            std::cout << " end of round " << gameRound + 1 << std::endl;
            gameRound++; //her turn 1 round
            turn = (gameRound % 2); //turn 0 ise player 2, turn 1 ise player 1 oynar oyuna ilk player 2 başlar
        } //while
    } //game loop fonksiyonu.
};

std::string getInput(std::string question, std::vector<std::string> inputs) {
    std::cout << question << std::endl;
    for (int i = 0; i < inputs.size(); i++) {
        std::cout << i + 1 << ") " << inputs.at(i) << std::endl;
    }
    int ch;
    std::cin >> ch;
    return inputs.at(ch - 1);
}

//*
//*
//*
//*
// *   GAME INT MAIN  *
//*
//*
int main() {


    //initscr();

    //MANA COST VECTORS FOR CREATURE CARDS

    std::vector<std::string> manaSoldier{ "W" };
    std::vector<std::string> manaArmoredPegasus{ "C","W" };
    std::vector<std::string> manaWhiteKnight{ "W","W" };
    std::vector<std::string> manaAngryBear{ "C","C","G","G" };
    std::vector<std::string> manaGuard{ "C","C","W","W" };
    std::vector<std::string> manaWerewolf{ "C","C","G","W" };
    std::vector<std::string> manaSkeleton{ "B" };
    std::vector<std::string> manaGhost{ "C","B" };
    std::vector<std::string> manaBlackKnight{ "B","B" };
    std::vector<std::string> manaOrcManiac{ "C","C","R","R" };
    std::vector<std::string> manaHobgoblin{ "C","R","B" };
    std::vector<std::string> manaVampire{ "C","C","C","B" };

    //MANA COST VECTORS FOR SORCERY CARDS

    std::vector<std::string> manaDisenchant{ "C","W" };
    std::vector<std::string> manaLightningBolt{ "C","G" };
    std::vector<std::string> manaFlood{ "C","G","W" };
    std::vector<std::string> manaReanimate{ "B" };
    std::vector<std::string> manaPlague{ "C","C","B" };
    std::vector<std::string> manaTerror{ "C","B" };

    //MANA COST VECTORS FOR ENCHANTMENT CARDS

    std::vector<std::string> manaRage{ "G" };
    std::vector<std::string> manaHolyWar{ "C","W" };
    std::vector<std::string> manaHolyLight{ "C","W" };
    std::vector<std::string> manaUnholyWar{ "C","B" };
    std::vector<std::string> manaRestrain{ "C","C","R" };
    std::vector<std::string> manaSlow{ "B" };

    //MANA VALUE VECTORS FOR LAND CARDS

    std::vector<std::string> manaForest{ "G" };
    std::vector<std::string> manaIsland{ "L" };
    std::vector<std::string> manaMountain{ "R" };
    std::vector<std::string> manaPlains{ "W" };
    std::vector<std::string> manaSwamp{ "B" };

    //CREATING CREATURE CARDS

    CreatureCard Soldier1("Soldier", (manaSoldier), "WHITE", 1, 1, 1, "Null");
    CreatureCard Soldier2("Soldier", (manaSoldier), "WHITE", 1, 1, 1, "Null");
    CreatureCard Soldier3("Soldier", (manaSoldier), "WHITE", 1, 1, 1, "Null");
    CreatureCard ArmoredPegasus1("ArmoredPegasus", (manaArmoredPegasus), "WHITE", 1, 2, 2, "Null");
    CreatureCard ArmoredPegasus2("ArmoredPegasus", (manaArmoredPegasus), "WHITE", 1, 2, 2, "Null");
    CreatureCard WhiteKnight1("WhiteKnight", (manaWhiteKnight), "WHITE", 2, 2, 2, "FirstStrike");
    CreatureCard WhiteKnight2("WhiteKnight", (manaWhiteKnight), "WHITE", 2, 2, 2, "FirstStrike");
    CreatureCard AngryBear("AngryBear", (manaAngryBear), "GREEN", 3, 2, 2, "Trample");
    CreatureCard Guard("Guard", (manaGuard), "WHITE", 2, 5, 5, "Null");
    CreatureCard Werewolf("Werewolf", (manaWerewolf), "GREEN", 4, 6, 6, "Trample");
    CreatureCard Skeleton1("Skeleton", (manaSkeleton), "BLACK", 1, 1, 1, "Null");
    CreatureCard Skeleton2("Skeleton", (manaSkeleton), "BLACK", 1, 1, 1, "Null");
    CreatureCard Skeleton3("Skeleton", (manaSkeleton), "BLACK", 1, 1, 1, "Null");
    CreatureCard Ghost1("Ghost", (manaGhost), "BLACK", 2, 1, 1, "Null");
    CreatureCard Ghost2("Ghost", (manaGhost), "BLACK", 2, 1, 1, "Null");
    CreatureCard BlackKnight1("BlackKnight", (manaBlackKnight), "BLACK", 2, 2, 2, "FirstStrike");
    CreatureCard BlackKnight2("BlackKnight", (manaBlackKnight), "BLACK", 2, 2, 2, "FirstStrike");
    CreatureCard OrcManiac("OrcManiac", (manaOrcManiac), "RED", 4, 1, 1, "Null");
    CreatureCard Hobgoblin("Hobgoblin", (manaHobgoblin), "RED", 3, 3, 3, "Null");
    CreatureCard Vampire("Vampire", (manaVampire), "BLACK", 6, 3, 3, "Null");

    //CREATING SORCERY CARDS

    SorceryCard Disenchant("Disenchant", (manaDisenchant), "WHITE");
    SorceryCard LightningBolt("LightningBolt", (manaLightningBolt), "GREEN");
    SorceryCard Flood1("Flood", (manaFlood), "GREEN");
    SorceryCard Flood2("Flood", (manaFlood), "GREEN");
    SorceryCard Reanimate("Reanimate", (manaReanimate), "BLACK");
    SorceryCard Plague("Plague", (manaPlague), "BLACK");
    SorceryCard Terror1("Terror", (manaTerror), "BLACK");
    SorceryCard Terror2("Terror", (manaTerror), "BLACK");

    //CREATING ENCHANTMENT CARDS

    EnchantmentCard Rage("Rage", (manaRage), "GREEN");
    EnchantmentCard HolyWar("HolyWar", (manaHolyWar), "WHITE");
    EnchantmentCard HolyLight("HolyLight", (manaHolyLight), "WHITE");
    EnchantmentCard UnholyWar("UnholyWar", (manaUnholyWar), "BLACK");
    EnchantmentCard Restrain("Restrain", (manaRestrain), "RED");
    EnchantmentCard Slow("Slow", (manaSlow), "BLACK");

    //CREATING LAND CARDS

    LandCard Forest1("Forest", (manaForest), "GREEN");
    LandCard Forest2("Forest", (manaForest), "GREEN");
    LandCard Forest3("Forest", (manaForest), "GREEN");
    LandCard Island1("Island", (manaIsland), "BLUE");
    LandCard Island2("Island", (manaIsland), "BLUE");
    LandCard Mountain1("Mountain", (manaMountain), "RED");
    LandCard Mountain2("Mountain", (manaMountain), "RED");
    LandCard Mountain3("Mountain", (manaMountain), "RED");
    LandCard Plains1("Plains", (manaPlains), "WHITE");
    LandCard Plains2("Plains", (manaPlains), "WHITE");
    LandCard Plains3("Plains", (manaPlains), "WHITE");
    LandCard Plains4("Plains", (manaPlains), "WHITE");
    LandCard Plains5("Plains", (manaPlains), "WHITE");
    LandCard Swamp1("Swamp", (manaSwamp), "BLACK");
    LandCard Swamp2("Swamp", (manaSwamp), "BLACK");
    LandCard Swamp3("Swamp", (manaSwamp), "BLACK");
    LandCard Swamp4("Swamp", (manaSwamp), "BLACK");
    LandCard Swamp5("Swamp", (manaSwamp), "BLACK");

    //2 MAIN PLAYERS DECKS VECTORS (LIBRARIES) ARRANGED ACCORDING TO PROJECT PAPERS(5)

    std::vector<std::shared_ptr<Card>> player1FirstDeck; //actually this will be the library1
    std::vector<std::shared_ptr<Card>> player2FirstDeck; //actually this will be the library2
    player1FirstDeck.reserve(26);
    player2FirstDeck.reserve(26);

    //2 MAIN PLAYERS HAND VECTORS ARRANGED
    std::vector<std::shared_ptr<Card>> player1HandDeck;
    std::vector<std::shared_ptr<Card>> player2HandDeck;
    player1HandDeck.reserve(7);
    player2HandDeck.reserve(7);

    //2 MAIN PLAYERS PLAY VECTORS ARRANGED
    std::vector<std::shared_ptr<Card>> player1PlayDeck;
    std::vector<std::shared_ptr<Card>> player2PlayDeck;

    //2 MAIN PLAYERS DISCARD VECTORS ARRANGED
    std::vector<std::shared_ptr<Card>> player1DiscardDeck;
    std::vector<std::shared_ptr<Card>> player2DiscardDeck;

    //player 1 cards pushed
    player1FirstDeck.push_back(std::make_shared<LandCard>(Plains1));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Plains2));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Plains3));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Plains4));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Plains5));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Forest1));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Forest2));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Forest3));
    player1FirstDeck.push_back(std::make_shared<LandCard>(Island1));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(Soldier1));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(Soldier2));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(Soldier3));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(ArmoredPegasus1));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(ArmoredPegasus2));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(WhiteKnight1));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(WhiteKnight2));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(AngryBear));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(Guard));
    player1FirstDeck.push_back(std::make_shared<CreatureCard>(Werewolf));
    player1FirstDeck.push_back(std::make_shared<SorceryCard>(Disenchant));
    player1FirstDeck.push_back(std::make_shared<SorceryCard>(LightningBolt));
    player1FirstDeck.push_back(std::make_shared<SorceryCard>(Flood1));
    player1FirstDeck.push_back(std::make_shared<SorceryCard>(Flood2));
    player1FirstDeck.push_back(std::make_shared<EnchantmentCard>(Rage));
    player1FirstDeck.push_back(std::make_shared<EnchantmentCard>(HolyWar));
    player1FirstDeck.push_back(std::make_shared<EnchantmentCard>(HolyLight));

    //player 2 cards pushed
    player2FirstDeck.push_back(std::make_shared<LandCard>(Swamp1));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Swamp2));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Swamp3));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Swamp4));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Swamp5));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Mountain1));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Mountain2));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Mountain3));
    player2FirstDeck.push_back(std::make_shared<LandCard>(Island2));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Skeleton1));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Skeleton2));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Skeleton3));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Ghost1));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Ghost2));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(BlackKnight1));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(BlackKnight2));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(OrcManiac));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Hobgoblin));
    player2FirstDeck.push_back(std::make_shared<CreatureCard>(Vampire));
    player2FirstDeck.push_back(std::make_shared<SorceryCard>(Reanimate));
    player2FirstDeck.push_back(std::make_shared<SorceryCard>(Plague));
    player2FirstDeck.push_back(std::make_shared<SorceryCard>(Terror1));
    player2FirstDeck.push_back(std::make_shared<SorceryCard>(Terror2));
    player2FirstDeck.push_back(std::make_shared<EnchantmentCard>(UnholyWar));
    player2FirstDeck.push_back(std::make_shared<EnchantmentCard>(Restrain));
    player2FirstDeck.push_back(std::make_shared<EnchantmentCard>(Slow));


    std::cout << "--------------GAME HAS STARTED  ----------------  " << std::endl;
    std::cout << "  " << std::endl;

    Player p1("Oyuncu1", (player1FirstDeck));
    Player p2("Oyuncu2", (player2FirstDeck));

    Game mainGame = Game(p1, p2); //oyunu initialize ettik

    mainGame.gameLoop();

    std::cout << " Game is Over " << std::endl;

    return 0;
}


