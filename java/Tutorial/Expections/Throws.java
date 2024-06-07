package Java_Code.Tutorial.Expections;

import java.rmi.RemoteException;

import javax.naming.InsufficientResourcesException;

public class Throws {
    public void deposit(double amount) throws RemoteException {
        throw new RemoteException();
    }

    public void withdraw(double amount) throws RemoteException, 
        InsufficientResourcesException {
        //Method implementation
    }
    //Remainder of class definition
}
