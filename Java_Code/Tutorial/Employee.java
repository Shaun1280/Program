package Java_Code.Tutorial;

import java.io.*;

public class Employee {

   String name;
   int age;
   String designation;
   double salary;

   public static double sSalary;

   public static final String DEPARTMENT = "Develop";

   public static void printSSalary() {
      System.out.println(sSalary);
   }

   // This is the constructor of the class Employee
   public Employee(String name) {
      this.name = name;
   }

   // Assign the age of the Employee  to the variable age.
   public void empAge(int empAge) {
      age = empAge;
   }

   /* Assign the designation to the variable designation.*/
   public void empDesignation(String empDesig) {
      designation = empDesig;
   }

   /* Assign the salary to the variable	salary.*/
   public void empSalary(double empSalary) {
      salary = empSalary;
   }

   /* Print the Employee details */
   public void printEmployee() {
      System.out.println("Name:"+ name );
      System.out.println("Age:" + age );
      System.out.println("Designation:" + designation );
      System.out.println("Salary:" + salary);
      System.out.println(DEPARTMENT + " average salary: " + sSalary);
   }
}