import processing.serial.*;
Serial port;
String data ;
Segment seg[]  = new Segment[3];
PVector base,base2;
float pozX, pozY; 
float initialPos[] = new float[3];
Segment yAxis;

void up(){
//System.out.println(seg[1].b.y);
    float y = seg[2].b.y - 1;
    seg[1].follow(seg[2].b.x-130,y);
   /// System.out.println(seg[1].b.y);
   // System.out.println("      ");
}
void down(){
//System.out.println(seg[1].b.y);
    float y = seg[2].b.y + 1;
    seg[1].follow(seg[2].b.x-130,y);
  //  System.out.println(seg[1].b.y);
  //  System.out.println("      ");
}

void right(){
float x = seg[2].b.x - 1 - 130;
   // System.out.println(seg[1].b.x);
    seg[1].follow(x,seg[2].b.y);
   // System.out.println(seg[1].b.x);
  //  System.out.println("      ");
}

void left(){
  float x = seg[2].b.x + 1 -130;
   // System.out.println(seg[1].b.x);
    seg[1].follow(x,seg[2].b.y);
   // System.out.println(seg[1].b.x);
    //System.out.println("      ");
}

void keyPressed(){
  if(key>'v' && key<'x'){
    up();
  }
   if(key>'r' && key<'t'){
    down();
  }
   if( key<'b'){
    right();
  }
   if(key>'c' && key<'e'){
    left();
  }
   if(key>'p' && key<'r'){
       float x = yAxis.b.x-1;
    yAxis.follow(x,yAxis.b.y);
    System.out.println(yAxis.b.x);
  }
  
   if(key>'d' && key<'f'){
       float x = yAxis.b.x+1;
    yAxis.follow(x,yAxis.b.y);
    System.out.println(yAxis.b.x);
  }
  
  
  data = "";
  float last_value = 0;
  for(int i=0;i<3;i++){
    last_value = (seg[i].angle -initialPos[i])*57.296 - last_value;
    data+=String.valueOf( last_value);
    data+=" | ";
  }
      data+=String.valueOf(-1.57 - yAxis.angle);
    System.out.print(data);
  port.write(data);
  System.out.println(" ");
  System.out.println("-----");
  
}


void setup() {
  port = new Serial(this, "COM4", 9600);

  size(800, 800);
  seg[0] = new Segment(100 , 100 , 150 ,-1.57+0.261);
  seg[0].update();
  for(int i=1;i<3;i++){
    seg[i] = new Segment(seg[i-1].b.x , seg[i-1].b.y , 150 ,0);
    seg[i].update();
  }
  seg[1].update();
  seg[2].len = 130;
  seg[2].update();
  base = new PVector(100,height-135);
  for(int i=0;i<3;i++){
    initialPos[i] = seg[i].angle;
  }
   yAxis = new Segment(width/2,300,200,-1.57);
     yAxis.update();

}

void draw() {
    background(51);
    stroke(255);
    strokeWeight(4);
    //inceput hanoi
    line(345,height-100,345,height-300);
    
    //turn hanoi
    line(400,height-120,400,height-220);
    
    //baza hanoi
    line(300,height-120,400,height-120);
    
    //baza polistiren
    line(100,height-100,300,height-100);

  for(int i=0;i<3;i++){
    seg[i].show();
  }
    seg[2].angle = 0;



  //  seg[1].follow(mouseX,mouseY);
    for(int i=1;i>0;i--){
      seg[i-1].follow(seg[i].a.x,seg[i].a.y);
    }
       seg[0].setA(base);

      for(int i=1;i<3;i++){
     seg[i].setA(seg[i-1].b);
    }
    
    
     
     base2 = new PVector(width/2,300);
              yAxis.setA(base2);

     yAxis.show();


}


///////////////

      


///////////////\
