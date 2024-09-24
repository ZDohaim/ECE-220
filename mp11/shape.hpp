/*This code uses Shape class which is the base class. Circle, Rectangle, Sphere, RectPrism are derived classes.
 The base class contains function getName() which return the name (Circle, Rectangle, Sphere, RectPrism)
 of an object. For each derived classes, you need to implement getArea(), getVolume(), and overloading operator
 "+" and operator "-". Your program should read the shapes defined in test.txt, and create a list of Shape pointers
 that points to objects of each input shape.*/

#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath> 
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>


using namespace std;

//#define PI 3.14159 // Defines a macro named M_PI with a value of 3.14159

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
    // public vs private:
    // includes everything, except
    
    //Base class' constructor should be called in derived classes'
    //constructor to initizlize Shape's private variable
      Shape(string name) {
          name_ = name; // makes name getter
          

    }
    
      string getName() {
          return name_;
    }
    
      virtual double getArea() const = 0;
      virtual double getVolume() const = 0;
    
private:
    string name_;
    
    


    
};



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
      Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
          // makes length and width global variable
          length_ = length;
          width_ = width;

    }
    
      double getArea() const {
          //area of R = length * width
          double areaRec = length_*width_;
          return (double) areaRec;
          
      }
    
      double getVolume() const{
          // volume of R = 0
          return (double) 0;

    }
    
    Rectangle<T> operator + (const Rectangle<T>& rec) {
        
        return *(new Rectangle<T>(length_ + rec.getLength(), width_ + rec.getWidth()));
    }
    
    Rectangle<T> operator - (const Rectangle<T>& rec) {
      
        return  *(new Rectangle<T>(max((T) 0.0, (T)width_ - (T)rec.getWidth()), max((T) 0.0, (T)length_ - (T) rec.getLength())));
    }
    
    // return width
    T getWidth() const {
        return (double) width_;
    }
    
    // return length
    T getLength() const {
        return (double) length_;
    }
    
private:
    T width_;
        T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-


class Circle : public Shape{
public:
      Circle(double radius):Shape("Circle"){
          // makes radius global variable
          radius_ = radius;
    }
    
    double getArea() const{
        //area of C = radius^2 * M_PI
        
        double areaCirc = pow(radius_,2) * M_PI;
        return (double) areaCirc;
        
    }
    
     double getVolume() const{
         //volume of C = 0
         double volCirc =0;
         return (double) volCirc;
    }
    
      Circle operator + (const Circle& cir){
          /*Given C3 = C1 + C2: it follows that
           radius C3 = radius C1 + radius C2*/
          return *(new Circle(radius_ +cir.getRadius()));
    }
    
    Circle operator - (const Circle& cir){
        /*Given C3 = C1 - C2: it follows that
         radius C3 = max(0, radius C1 - radius C2)*/
        return *(new Circle(radius_ - cir.getRadius()));
    }
    //return radius
    double getRadius() const {
        return (double) radius_;
    }
    
private:
    double radius_;

};


//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-


class Sphere : public Shape{
public:
      Sphere(double radius):Shape("Sphere") {
          radius_ = radius;
    }

      double getVolume() const {
          //volume of S = (4.0 / 3.0) * radius^3 * M_PI
          double volSphere = ((4.0 / 3.0) * (pow(radius_, 3)) * M_PI);
          return (double) volSphere;
    }
    
      double getArea() const {
          //area of S = 4 * M_PI * radius^2
          double areaSphere = 4 * M_PI * pow (radius_, 2);
          return (double) areaSphere;
    }
    
    Sphere operator + (const Sphere& sph) {
      
        return *(new Sphere(radius_ + sph.getRadius()));
    }

    Sphere operator - (const Sphere& sph) {
       
        return *(new Sphere(radius_ - sph.getRadius()));
    }
    
    //return radius
    double getRadius() const {
        return (double) radius_;

    }

private:
    double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-

class RectPrism : public Shape{
public:
      RectPrism(double width, double length, double height):Shape("RectPrism") {
          length_ = length;
          width_ = width;
          height_ = height;
    }
    
      double getVolume() const {
          //volume of RP =  length * width * height
          double volPrism = (length_*width_*height_);
          return (double) volPrism;
    }
      
    double getArea() const {
        // area of RP = 2 * (l ength *  width  + length * height + width * height)
        double areaPrism = 2 *((length_* width_) + (length_ * height_) + (width_*height_));
        
        return (double) areaPrism;


    }
    
    RectPrism operator + (const RectPrism& rectp){
        double newLength = length_ + rectp.getLength();
        double newWidth = width_ + rectp.getWidth();
        double newHeight = height_ + rectp.getHeight();
        return *(new RectPrism(newWidth, newLength, newHeight));
    }
    
    RectPrism operator - (const RectPrism& rectp){
      
        double newLength = max( (double) 0, length_ - rectp.getLength());
        double newWidth = max((double) 0, width_ - rectp.getWidth());
        double newHeight = max((double) 0, height_ - rectp.getHeight());
        return *(new RectPrism(newWidth, newLength, newHeight));
        
    }
    
    //return width as a double
    double getWidth() const {
        return (double) width_;
    }
    
    //return length as a double
    double getLength() const {
        return (double) length_;
    }
    
    // return height as a double
    double getHeight() const {
        return (double) height_;
    }
  
private:
      double length_;
      double width_;
      double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
static list<Shape*> CreateShapes(char* file_name) {
    //@@Insert your code here
    // create list of pointer (list<Shape*> point to the objects initialized according to the input data.
    // reads file
    int listNum = 0;
    string filename;
    ifstream ifs(file_name, std::ifstream::in);
    // gets name of shape and r from file
    ifs >> listNum;
    list<Shape*> shapes;
    while (!(listNum == 0)){
        string shapeTyp;
        //declare variables
        double radius;
        double length;
        double width;
        double height;
        // shape_ptr points to Shape
        Shape* shape_ptr;
        ifs >> shapeTyp;
        
        if(shapeTyp == "Rectangle"){
            ifs >> width >> length;
            // printf("%d ", ifs);
            shape_ptr = new Rectangle <double>
            (width, length);
            shapes.push_back(shape_ptr);
        } else if(shapeTyp == "Circle"){
            ifs >> radius;
            shape_ptr = new Circle(radius);
            //add an element to the back of the list
             // printf("%d ", ifs);
            shapes.push_back(shape_ptr);
        } else if(shapeTyp == "Sphere"){
            ifs >> radius;
            // printf("%d ", ifs);
            // new allocates memory (malloc)
            shape_ptr = new Sphere(radius);
            shapes.push_back(shape_ptr);
        } else if (shapeTyp == "RectPrism"){
            ifs >> width >> length >> height;
             // printf("%d ", ifs);
            shape_ptr = new RectPrism(width, length, height);
            shapes.push_back(shape_ptr);
        }
        // decrement list counter to check for other shapes
        listNum --;
    }
    ifs.close();
    return shapes;
}



// call getArea() of each object
// return the max area

static double MaxArea(list<Shape*> shapes){
    double max_area = 0;
    //@@Insert your code here
    // iterates through list, from start to end
    for (list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++) {
        // check if area is greater than max
        // printf("%d ", *it);
        if ((*it) -> getArea() > max_area){
            max_area = (*it) -> getArea();
            
        }
    }
    
    return (double) max_area;
}

// call getVolume() of each object
// return the max volume

static double MaxVolume(list<Shape*> shapes){
    double max_volume = 0.0;
    //@@Insert your code here
    // iterate thorugh list from start to end
    // printf("%d ", *it);
    for (list<Shape*>::iterator it =shapes.begin(); it != shapes.end(); it++) {
        if((*it)-> getVolume() > max_volume){
            max_volume = (*it) -> getVolume();
        }
    }
    return (double) max_volume;
}
#endif