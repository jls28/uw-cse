
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;
import java.util.*;

public class OverHundredGui implements ActionListener {
	
	private JTextPane area;
	private JTextField count;
	private JButton compute;
	
	
	public OverHundredGui() {
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		frame.setSize(600,768);
		frame.setTitle("Line Length Checker");
		
		area = new JTextPane();
		count = new JTextField(5);
		count.setText("100");
		compute = new JButton("Check");
		JPanel south = new JPanel(new GridLayout(1,2));
		south.add(count);
		south.add(compute);
		frame.add(new JScrollPane(area), BorderLayout.CENTER);
		frame.add(south, BorderLayout.SOUTH);
		
		compute.addActionListener(this);

		frame.setVisible(true);
	}
	
	
	//delete what's in text area
	//loop through each line
	//check if string is longer than count text field
	//print string red if longer, otherwise print black
	
	private void lengthChecker() {
		Scanner input = new Scanner(area.getText());
		area.setText("");
		int maxLength = Integer.parseInt(count.getText());
		while(input.hasNextLine()) {
			String line = input.nextLine();
			if (line.length() > maxLength) {
				appendToPane(area, line + "\n", Color.RED);
			} else {
				appendToPane(area, line + "\n", Color.BLACK);
			}	
		}
	}
	private void appendToPane(JTextPane textPane, String message, Color c)
    {
        StyleContext style = StyleContext.getDefaultStyleContext();
        AttributeSet attributes = style.addAttribute(SimpleAttributeSet.EMPTY, StyleConstants.Foreground, c);

        attributes = style.addAttribute(attributes, StyleConstants.FontFamily, "count.getFont()");
        attributes = style.addAttribute(attributes, StyleConstants.Alignment, StyleConstants.ALIGN_JUSTIFIED);

        int length = textPane.getDocument().getLength();
        textPane.setCaretPosition(length);
        textPane.setCharacterAttributes(attributes, false);
        textPane.replaceSelection(message);
    }
	
	public void actionPerformed(ActionEvent event) {
		lengthChecker();
	}

}
