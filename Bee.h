#ifndef BEE_H
#define BEE_H


class Bee
{
    public:
        float x,y,z,radius;
        Bee();
        Bee(float x, float y, float z,float radius);
        void render();

    protected:

    private:
        void drawBee();
};

#endif // BEE_H
