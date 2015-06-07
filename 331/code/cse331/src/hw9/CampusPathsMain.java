package hw9;

import hw8.*;

/**
 * Stefan Dierauf Nov 2014
 *
 * Main for CampusPaths GUI version. Instantiates the GUI, which contains
 * the view and the controller, and the model.
 */
public class CampusPathsMain {

  public static void main(String[] args) {

    CampusPathsModel model = new CampusPathsModel();
    CampusPathsGui gui = new CampusPathsGui(model);

    //get the view from the gui and set it as an observer of the model
    model.addView(gui.getView());

    //Give the buildings to the view
    model.outputBuildings();
  }
}
