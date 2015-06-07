package hw9;
import hw5.Edge;
import hw8.CampusPathsModel;
import hw8.CampusPathsView;
import hw8.PixelPoint;

import java.util.List;
import java.util.Map;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;



/**
 * Stefan Dierauf Nov 2014
 *
 * Main GUI class for CampusPaths
 *
 * General layout:
 * ----------------------
 * |                    |
 * |                    |
 * |        map         |
 * |                    |
 * ----------------------
 * |      controls      |
 * ----------------------
 *
 * The map section displays an image of campus. When two buildings are selected in controls
 * and the 'route' button is clicked, a path between the two buildings is drawn on the map.
 *
 * CampusPathsGui has no abstraction function or representation invariant, because it does
 * not represent an ADT
 *
 */
public class CampusPathsGui {

  /**
   * @specfield view The view to be output to from the model.
   * @specfield model A reference to the model
   * @specfield mapPanel The 'map' part of the GUI
   * @specfield controlPanel The 'controls' part of the GUI
   */
  private CampusPathsView view;
  private CampusPathsModel model;
  private CampusPathsMapComponent mapPanel;
  private CampusPathsControlPanel controlPanel;


  /**
   * Constructs a new CampusPathsGui
   * @param model
   * @effects Constructs a new CampusPathsGui
   */
  public CampusPathsGui(CampusPathsModel model) {
    this.model = model;
    this.view = new CampusPathsGUIView();
    initializeFrame();
  }

  /**
   * Sets up the layout and JPanels.
   * @effects initializes this.mapPanel and this.controlPanel
   */
  private void initializeFrame() {
    JFrame frame = new JFrame("Campus Paths");
    frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    frame.setPreferredSize(new Dimension(1024, 768));
    JPanel mainPanel = new JPanel();
    LayoutManager mainLayout = new BorderLayout();
    mainPanel.setLayout(mainLayout);
    mapPanel = new CampusPathsMapComponent(mainPanel);
    mainPanel.add(mapPanel, BorderLayout.CENTER);
    controlPanel = new CampusPathsControlPanel(this.model, mapPanel);
    mainPanel.add(controlPanel, BorderLayout.SOUTH);
    frame.add(mainPanel);
    frame.pack();
    frame.setVisible(true);
  }

  /**
   * @return this.view for registration with the model
   */
  public CampusPathsView getView() {
    return this.view;
  }


  /**
   * Internal CampusPathsView
   * @see hw8.CampusPathsView for more information
   *
   * Routes broadcasts from the model to the correct parts of the GUI
   */
  private class CampusPathsGUIView implements CampusPathsView {

    /**
     * @effects constructs a new CampusPathsGUIView
     */
    public CampusPathsGUIView() {

    }



    /**
     * Updates the parent's controlPanel to contain the available buildings to find routes between
     * @see hw8.CampusPathsView#displayBuildings(java.util.Map)
     * @param buildings map of short to long building names
     */
    @Override
    public void displayBuildings(Map<String, String> buildings) {
      controlPanel.updateMenuItems(buildings);
    }

    /**
     * Draws the path between two buildings
     * @see hw8.CampusPathsView#displayPath(String, String, java.util.List, hw8.PixelPoint)
     * @param start building long name
     * @param end building long name
     * @param path list of Edges that make up the path
     * @param startPoint starting PixelPoint of the path
     */
    @Override
    public void displayPath(String start, String end, List<Edge<PixelPoint, Double>> path, PixelPoint startPoint) {
      mapPanel.setPath(startPoint, path);
      mapPanel.repaint();
    }


    /**
     * ////////////////////////// Unused methods from Interface ///////////////////////////
     */

    @Override
    public void start() {

    }

    @Override
    public void unknownOption() {

    }

    @Override
    public void unknownBuildings(List<String> buildings) {

    }

    @Override
    public void showMenu() {

    }

    @Override
    public void promptStartBuilding() {

    }

    @Override
    public void promptEndBuilding() {

    }

    @Override
    public void println(String output) {

    }
  }
}
