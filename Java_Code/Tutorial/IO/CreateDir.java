package Java_Code.Tutorial.IO;

import java.io.File;

public class CreateDir {

   public static void main(String args[]) {
      String dirname = "./tmp/user/java/bin";
      File d = new File(dirname);

      System.out.println();
      
      // Create directory now.
      d.mkdirs();
   }
}
