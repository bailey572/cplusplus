#ifndef BASIC_MATH_H
#define BASIC_MATH_H

/*
* BasicMath is a collection of static math functions accessible directly through
* the functions without requiring the instantiation of a class object.
*/
class BasicMath{
  public:
    
    /*
    * Retrieve current version of the class
    */
    constexpr static double get_version(){return BasicMath::version;}
    /*
    * Return SUM of two passed in integers
    */
    static int add(int x=0, int y=0){return x+y;}
     /*
    * Return SUM of two passed in doubles
    */
    static double add(double x=0.0, double y=0.0){return x+y;}
    /*
    * Return Product of two passed in integers
    */
    static int multiply(int x=0, int y=0){return x*y;}
     /*
    * Return Product of two passed in doubles
    */
    static double multiply(double x=0.0, double y=0.0){return x*y;}
  private:
    /*
    * Basic constructor used to initialize instance of the class
    * Not utilized in this class so hidden behind private access level
    */
    BasicMath();
    /*
    * Basic destructor used to destroy instance of the class
    * Not utilized in this class so hidden behind private access level
    */
    ~BasicMath();
    static constexpr double version = 0.1;
};

#endif  /* BASIC_MATH_H */