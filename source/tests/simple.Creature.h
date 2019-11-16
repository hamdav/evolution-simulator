#ifndef CREATURE
#define CREATURE

class Creature
{
    private:
        float number;
        float score;
    public:
        float getNumber();
        void setScore(float s);
        float getScore();
        Creature offspring();
        Creature(float n);
        Creature();
};

#endif

        
        
