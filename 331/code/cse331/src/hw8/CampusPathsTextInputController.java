package hw8;

import java.io.InputStream;
import java.util.Scanner;

/**
 * Stefan Dierauf Nov 2014
 *
 * CampusPathsTextInputController represents a controller that listens and interprets a textual input stream.
 * The controller then calls methods on the model based on it's input.
 *
 * Representation invariant:
 * this.model != null
 *
 * Abstraction function;
 * CampusPathsTextInputController listens for input on this.in,
 * and then calls corresponding functions on this.model
 */

public class CampusPathsTextInputController implements CampusPathsController {

  /**
   * @specfield model: the model this will call functions on
   * @specfield input: the Scanner on the passed InputStream
   */

  private CampusPathsModel model;
  private Scanner input;

  /**
   * Builds a new CampusPathsTextInputController
   * @requires in != null && model != null
   * @param in
   * @param model
   */
  public CampusPathsTextInputController(InputStream in, CampusPathsModel model) {
    this.model = model;
    this.input = new Scanner(in);
  }

  /**
   * Starts listening on this.input's InputStream
   */
  @Override
  public void listen() {
    String command = "";
    while (!command.equals("q")) {
      command = input.nextLine();
      if (command.length() == 1 && "brqm".contains(command)) {
        handleCommand(command);
      } else if (command.length() == 0 || command.charAt(0) == '#') {
        //handle case if it's a comment or just an empty newline
        for (CampusPathsView view : model.getObservers()) {
          view.println(command);
        }
      } else {
        //don't know what the user wants to do
        for (CampusPathsView view : model.getObservers()) {
          view.unknownOption();
        }
      }
    }
    input.close();
  }

  /**
   * Prompts the user through this.model's observers for a starting building and an ending building
   * and then calls computeRoute on the model
   */
  private void promptRoute() {
    for (CampusPathsView view : model.getObservers()) {
      view.promptStartBuilding();
    }
    String start = input.nextLine().trim();
    for (CampusPathsView view : model.getObservers()) {
      view.promptEndBuilding();
    }
    String end = input.nextLine().trim();
    model.computeRoute(start, end);
  }

  /**
   * Calls the appropriate command based on the input
   * Only handles the following commands:
   * b: tells the model to display it's buildings
   * r: starts the route prompt
   * m: tells this.model's views to show their menus
   * @param command
   */
  private void handleCommand(String command) {
    switch (command) {
      case "b":
        model.outputBuildings();
        break;
      case "r":
        promptRoute();
        break;
      case "m":
        for (CampusPathsView view : model.getObservers()) {
          view.showMenu();
        }
        break;
    }
  }

}
