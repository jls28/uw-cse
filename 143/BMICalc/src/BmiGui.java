// a gui to compute someones bmi
//no event handling

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class BmiGui implements ActionListener{
	private JTextField heightField;
	private JTextField weightField;
	private JLabel bmiLabel;
	
	public BmiGui() { 
		//set up components
		heightField = new JTextField(5);
		weightField = new JTextField(5);
		bmiLabel = new JLabel(" Enter your height and weight");
		JButton computeButton = new JButton("Compute");
		
		computeButton.addActionListener(this);
		
		//layout
		JPanel north = new JPanel(new GridLayout(2,2));
		north.add(new JLabel("Height: "));
		north.add(heightField);
		north.add(new JLabel("Weight: "));
		north.add(weightField);
		
		//overall frame
		JFrame frame = new JFrame("BMI");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		frame.add(north, BorderLayout.NORTH);
		frame.add(bmiLabel, BorderLayout.CENTER);
		frame.add(computeButton, BorderLayout.SOUTH);
		frame.pack();
		frame.setVisible(true);
		
	}
	
	public void actionPerformed(ActionEvent event) {
		double height = Double.parseDouble(heightField.getText());
		double weight = Double.parseDouble(weightField.getText());
		
		double bmi = weight / (height * height) * 703;
		bmiLabel.setText("BMI: " + bmi);
	}
	

}
