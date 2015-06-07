package hw8.test;

import hw8.CampusPathsModel;
import hw8.CampusPathsTextView;
import hw8.CampusPathsView;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import static org.hamcrest.CoreMatchers.not;
import static org.junit.Assert.*;

/**
 * Stefan Dierauf Nov 2014
 *
 * Tests the public methods of CampusPathsModel
 */
public class CampusPathsModelTest {

  @Test
  public void testInstantiation() {
    CampusPathsModel model = new CampusPathsModel();
  }

  @Test
  public void testAddView() {
    CampusPathsModel model = new CampusPathsModel();
    CampusPathsView view = new CampusPathsTextView(System.out);
    model.addView(view);
    assertTrue(model.getObservers().size() == 1);
    assertTrue(model.getObservers().contains(view));
  }

  @Test
  public void testGetObservers() {
    CampusPathsModel model = new CampusPathsModel();
    CampusPathsView view = new CampusPathsTextView(System.out);
    model.addView(view);
    model.getObservers();
  }

  @Test
  public void testDeleteView() {
    CampusPathsModel model = new CampusPathsModel();
    CampusPathsView view = new CampusPathsTextView(System.out);
    model.addView(view);
    model.deleteView(view);
    assertTrue(model.getObservers().size() == 0);
  }

}
