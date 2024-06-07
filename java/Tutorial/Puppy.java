package Java_Code.Tutorial;

import java.io.*;

public class Puppy {
    int puppyAge;

    public Puppy(String name) {
        System.out.println("Passed name is :" + name);
    }

    public void setAge(int age) {
        puppyAge = age;
    }

    public void getAge() {
        System.out.println("Puppy's age is :" + puppyAge);
        //return puppyAge;
    }

    public static void main(String args[]) {
        Puppy myPuppy = new Puppy("tommy");
        
        myPuppy.setAge(2);

        myPuppy.getAge();

        System.out.println("Variable value : " + myPuppy.puppyAge);
    }
}
