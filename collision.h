#ifndef COLLISION_H
#define COLLISION_H


class collision
{
    public:
        collision();
        void detectCollision();
        double calDistance();
    protected:

    private:
        double distance;
        Backyard by;
        Bee b;
        Flowers flwr;
        Windmill wm;
        Tree tr;
        Sprinkler spr;
        Person pers;


};

#endif // COLLISION_H
