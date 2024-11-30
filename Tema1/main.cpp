#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <memory>

class Sportsman
{
    protected:
        std::string firstName;
        std::string lastName;
        int age;
    
    public:
        // constructor
        Sportsman(const std::string& firstName, const std::string& lastName, int age)
            : firstName(firstName), lastName(lastName), age(age)
            {
                std::cout << "The Sportsman constructor has been invoked for " << this->getFullName() << std::endl;
            }

        // copy constructor
        Sportsman(const Sportsman& s)
            : firstName(s.firstName), lastName(s.lastName), age(s.age)
            {
                std::cout << "The Sportsman COPY constructor has been invoked for " << this->getFullName() << std::endl;
            }

        // Sportsman(const Sportsman& s) = delete;

        // move constructor
        Sportsman(Sportsman&& s)
            : firstName(std::move(s.firstName)), lastName(std::move(s.lastName)), age(std::move(s.age))
            {
                std::cout << "The Sportsman MOVE constructor has been invoked for " << this->getFullName() << std::endl;
            }

        // Sportsman(Sportsman&& s) = delete;

        std::string getFullName() const
        {
            return firstName + " " + lastName;
        }

        void setFirstName(std::string name){
            firstName = name;
            std::cout <<"First name has been modified!" << std::endl;
        }

        void setLastName(std::string name){
            lastName = name;
            std::cout << "Last name has been modified!" << std::endl;
        }

        int getAge() const
        {
            return age;
        }

        void setAge(int age)
        {
            this->age = age;
            std::cout << "Age has been modified!" << std::endl;
        }

        virtual void displaySportsmanInfo()
        {
            std::cout << "\n" << "Name: " << getFullName() << "\n"
                << "Age: " << age << std::endl;
        }

        ~Sportsman()
        {
            std::cout << "Sportsman destructor has been called for " << this->getFullName() << std::endl;
        }
};

class FootballPlayer : public Sportsman
{
    private:
        std::string position;
        std::string team;
        int goals;
        std::mutex goalsMutex;

    public:
        // constructor
        FootballPlayer(const std::string& firstName, const std::string& lastName, int age, const std::string& position, const std::string& team)
            : Sportsman(firstName, lastName, age), position(position), team(team), goals(0)
            {
                std::cout << "The FootballPlayer constructor has been invoked for " << this->getFullName() << std::endl;
            }

        // copy constructor
        FootballPlayer(const FootballPlayer& f)
            : Sportsman(f), position(f.position), team(f.team), goals(f.goals)
            {
                std::cout << "The FootballPlayer COPY constructor has been invoked for " << this->getFullName() << std::endl;
            }

        // FootballPlayer(const FootballPlayer& f) = delete;

        // move constructor
        FootballPlayer(FootballPlayer&& f)
            : Sportsman(std::move(f)), position(std::move(f.position)), team(std::move(f.team)), goals(std::move(f.goals))
            {
                std::cout << "The FootballPlayer MOVE constructor has been invoked for " << this->getFullName() << std::endl;
            }
        
        // FootballPlayer(FootballPlayer&& f) = delete;

        std::string getPosition() const
        {
            return position;
        }

        void setPosition(std::string position)
        {
            this->position = position;
            std::cout <<"Position has been modified!" << std::endl;
        }

        std::string getTeam() const
        {
            return team;
        }

        void setTeam(std::string team)
        {
            this->team = team;
            std::cout << "Team has been modified!" << std::endl;
        }

        int getGoals() const
        {
            return goals;
        }

        void scoreGoal()
        {
            std::lock_guard<std::mutex> lock(goalsMutex); // Lock the mutex
            goals++;
            std::cout << "A goal has been scored!" << std::endl;
        }

        void displaySportsmanInfo()
        {
            Sportsman::displaySportsmanInfo();
            std::cout << "Position: " << position << "\n"
                << "Team: " << team << "\n"
                << "Goals scored: " << goals << std::endl;
        }

        FootballPlayer& operator=(const FootballPlayer& fp);

        ~FootballPlayer()
        {
            std::cout << "FootballPlayer destructor has been called for " << this->getFullName() << std::endl;
        }
};


FootballPlayer& FootballPlayer::operator=(const FootballPlayer& fp)
{
    firstName = fp.firstName;
    lastName = fp.lastName;
    age = fp.age;
    position = fp.position;
    team = fp.team;
    goals += fp.goals;
    return *this;
}

// wrapper method needed for working with threads
void scoreGoalsConcurrently(FootballPlayer& player, int numGoals)
{
    for (int i = 0; i < numGoals; ++i)
    {
        player.scoreGoal();
    }
}

int main()
{
    FootballPlayer *fp1 = new FootballPlayer("Lionel", "Messi", 37, "CF", "Inter Miami");
    FootballPlayer *fp2 = new FootballPlayer("Cristiano", "Ronaldo", 39, "ST", "Al Nassr");

    Sportsman *s = new FootballPlayer("Gheorghe", "Hagi", 40, "CAM", "Steaua Bucuresti");
    Sportsman *s1 = new Sportsman(*s); // use copy constructor

    FootballPlayer fp3("Adrian", "Mutu", 30, "ST", "Fiorentina");
    FootballPlayer fp4 = fp3;   // use copy constructor

    FootballPlayer fp5("Lamine", "Yamal", 17, "RW", "FC Barcelona");

    // display objects' info
    fp1->displaySportsmanInfo();
    fp2->displaySportsmanInfo();
    s->displaySportsmanInfo();
    s1->displaySportsmanInfo();
    fp3.displaySportsmanInfo();
    fp4.displaySportsmanInfo();
    fp5.displaySportsmanInfo();

    FootballPlayer fp6 = std::move(fp5);    // use move constructor
    fp6.displaySportsmanInfo();

    // make changes on new reference and see what happens with the old one as well
    for(int i = 0; i < 3; i++) fp6.scoreGoal();
    fp5.displaySportsmanInfo();
    fp6.displaySportsmanInfo();

    std::cout << "\n" << "CONSTRUCTORS ZONE DONE!" << "\n" << std::endl;

    // work with unique pointers
    std::unique_ptr<FootballPlayer> fp7(new FootballPlayer("Cristian", "Chivu", 37, "CF", "Inter Milano"));
    fp7->displaySportsmanInfo();
    fp7->scoreGoal();
    std::unique_ptr<FootballPlayer> fp8 = std::move(fp7);   // transfer ownership from fp7 to fp8
    //fp7->displaySportsmanInfo(); // generates an error
    fp8->displaySportsmanInfo();

    // work with shared pointers
    std::shared_ptr<FootballPlayer> fp9(new FootballPlayer("Andres", "Iniesta", 40, "CM", "Barcelona"));
    std::shared_ptr<FootballPlayer> fp10 = fp9; // share ownership between fp9 and fp10

    // check if both references point to the same object
    std::cout << "fp9 is pointing to: " << fp9->getFullName() << std::endl;
    std::cout << "fp10 is pointing to: " << fp10->getFullName() << std::endl;

    // make a change through one of the "owners" and then check another one to see if the changes are visible for all "owners"
    fp9->scoreGoal();
    std::cout << fp10->getGoals() << std::endl;
    
    // modify some attributes
    fp1->setFirstName("Lionel Andres");
    fp1->setAge(25);
    fp1->setTeam("FC Barcelona");
    fp1->setPosition("RW");

    fp2->setAge(27);
    fp2->setTeam("Real Madrid");
    fp2->setPosition("LW");

    s->setAge(59);
    s1->setFirstName("Ianis");
    s1->setAge(25);

    for(int i = 0; i < 10; i++)
    {
        if(i < 2) fp6.scoreGoal();
        if(i < 5) fp2->scoreGoal();
        fp1->scoreGoal();
    }

    // goals scored with threads
    std::thread t1(scoreGoalsConcurrently, std::ref(fp4), 5); // thread 1: fp4 scores 5 goals
    std::thread t2(scoreGoalsConcurrently, std::ref(fp4), 7); // thread 2: fp4 scores 7 goals

    // join threads to ensure all threads complete
    t1.join();
    t2.join();

    fp1->displaySportsmanInfo();
    fp2->displaySportsmanInfo();
    s->displaySportsmanInfo();
    s1->displaySportsmanInfo();
    fp3.displaySportsmanInfo();
    fp4.displaySportsmanInfo(); // here fp4 should have 12 goals
    fp5.displaySportsmanInfo();
    fp6.displaySportsmanInfo();

    *fp2 = *fp1;    // demonstrate the overloading of the assignment operator

    fp1->displaySportsmanInfo();
    fp2->displaySportsmanInfo();

    delete fp1;
    delete fp2;
    delete s;
    delete s1;

    return 0;
}