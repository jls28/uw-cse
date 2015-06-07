package hw8;

import java.io.InputStream;
import java.io.PrintStream;

/**
 * Stefan Dierauf Nov 2014
 *
 * CampusPathsMain main method for the program
 * Input/Output via command line
 */
public class CampusPathsMain {


  /**
   * main method
   * @param args required
   */
  public static void main(String[] args) {
    CampusPathsModel model = new CampusPathsModel();
    CampusPathsView view = new CampusPathsTextView(System.out);
    model.addView(view);
    CampusPathsController textInput = new CampusPathsTextInputController(System.in, model);
    view.start();
    textInput.listen();
  }


}
