#include "collision.h"
#include "math.h"
collision::collision()
{
    //ctor
}


double collision::calDistance(Obj o){
double dist1= pow((o.x-b.x),2)+((o.y-b.y),2)+((o.z-b.z),2);
distance=sqrt(dist1);
return distance;
}
void collision::detectCollision(Bee b){
if(calDistance()+0.75==0){
    b.x++;
}
if(b.x==by.x && b.y==by.y && b.z==by.z){
    b.x++;
    b.z--;
    b.y++;
}
else if(b.x==flwr.x && b.y==flwr.y && b.z==flwr.z){
    b.x++;
    b.z--;
    b.y++;
}
else if(b.x==pers.x && b.y==pers.y && b.z==pers.z){
    b.x++;
    b.z--;
    b.y++;
}
else if(b.x==wm.x && b.y==wm.y && b.z==wm.z){
    b.x++;
    b.z--;
    b.y++;
}
else if(b.x==tr.x && b.y==tr.y && b.z==tr.z){
    b.x++;
    b.z--;
    b.y++;
}
else{
    b.movePlayer();
}

}
