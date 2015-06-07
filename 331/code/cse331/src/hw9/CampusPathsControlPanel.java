package hw9;

import hw8.CampusPathsModel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import javax.swing.*;
import java.awt.*;

/**
 * Stefan Dierauf Nov 2014
 * Control Panel GUI element for CampusPaths
 *
 * layout:
 * -------------------------------------------------------
 * | Start: [Building1] End: [Building2] [Route] [Clear] |
 * -------------------------------------------------------
 *
 * Where [Building1] and [Building2] are both dropdowns containing
 * all possible locations on campus and [Route] tells the model to
 * compute the route. [Clear] clears all paint off the map.
 *
 * CampusPathsControlPanel has no abstraction function or representation invariant, because it does
 * not represent an ADT
 *
 */
public class CampusPathsControlPanel extends JPanel {

  /**
   * @specfield startList A JComboBox containing all possible start locations
   * @specfield endList A JComboBox containing all possible ending locations
   */
  private JComboBox<String> startList;
  private JComboBox<String> endList;

  /**
   * @param model The model to be registered to the actionlistener
   * @param map The map to clear with the [Clear] button
   * @effects constructs a new CampusPathsControlPanel
   */
  public CampusPathsControlPanel(final CampusPathsModel model, final CampusPathsMapComponent map) {
    JLabel startLabel = new JLabel();
    startLabel.setText("Start:");
    JLabel endLabel = new JLabel();
    endLabel.setText("End:");
    this.startList = new JComboBox<String>();
    this.endList = new JComboBox<String>();
    JButton calcButton = new JButton();
    calcButton.setText("Route");
    //Add action listener for clicking on the route button computes a paths
    calcButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        int startIndex = startList.getSelectedIndex();
        int endIndex = endList.getSelectedIndex();
        if (startIndex == -1 || endIndex == -1) {
          return;
        }
        String startShortName = startList.getItemAt(startIndex);
        String endShortName = endList.getItemAt(endIndex);
        model.computeRoute(startShortName, endShortName);
      }
    });
    JButton resetButton = new JButton();
    resetButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        map.clearPath();
        map.repaint();
      }
    });
    resetButton.setText("Clear");
    this.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
    this.add(startLabel);
    this.add(startList);
    this.add(endLabel);
    this.add(endList);
    this.add(calcButton);
    this.add(resetButton);
  }

  /**
   * Updates the contents of the location ComboBoxes with data from buildings
   * @param buildings Data to update the lists with
   */
  public void updateMenuItems (Map<String, String> buildings) {
    //Empty the lists
    startList.removeAllItems();
    endList.removeAllItems();

    for (String shortName : buildings.keySet()) {
      startList.addItem(shortName);
      endList.addItem(shortName);
    }
  }



}
