
class Segment{
  PVector a;
  float angle;
  float len;
  PVector b = new PVector();
  Segment parent;
  Segment(float x,float y,  float len_,float angle_){
    a = new PVector(x,y);
    angle = angle_;
    len = len_;
    calculateB();
  }
  
   Segment(Segment parent_,  float len_,float angle_){
    parent = parent_;
    a = parent.b.copy();
    len = len_;
    angle = angle_;
        calculateB();
  }
  
  void calculateB(){
    float bx = len * cos(angle) + a.x;
    float by = len * sin(angle) + a.y;
    b.set(bx,by);
  }
  
  void update(){
    calculateB();
  }
  
  void setA(PVector pos){
    a = pos.copy();
    calculateB();
  }
  
  void follow(float tx,float ty){
    PVector target =  new PVector(tx,ty);
    PVector dir = PVector.sub(target,a);
    angle = dir.heading(); 
    //System.out.println(angle);
    dir.setMag(len);
    dir.mult(-1);
    a = PVector.add(target,dir);
    update();  
  }
  
  void show(){
    stroke(255);
    strokeWeight(4);
    line(a.x,a.y,b.x,b.y);
  }
}
