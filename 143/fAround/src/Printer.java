
public class Printer {
	String[] rawData;
	//by index:location | boxes of paper | slides |  printer | lastactive | NG | comments
	double reams;
	double slides;
	String comments;
	
//	public Printer() {
//		this("unnamed", "00");
//	}
//	
//	public Printer(String name, String lastActive) {
//		this(name, -1, -1, " ", lastActive);
//	}
//	
//	public Printer(String name, double paper, double slides, String comments, String lastActive) {
//		this.name = name;
//		location = name.replaceAll("[psc]", "");
//		reams = paper;
//		this.slides = slides;
//		this.comments = comments;
//		this.lastActive = lastActive;
//	}
	
	public Printer(String dataStream) {
		this.rawData = (dataStream + " ").split("[|]");
//		for (int i = 0; i < data.length; i++) {
//			System.out.println(data[i]);
//		}
		this.reams = parseReams();
		this.slides = parseSlides();
		this.comments = parseComments();
	}
	
	public double parseReams() {
		String data = rawData[1].trim();
		//System.out.println(data);
		if (data.length() == 0) {
			return -1;
		}
		return Double.parseDouble(data);
	}
	
	public double parseSlides(){
		String data = rawData[2].trim();
		if (data.contains("NA")) {
			return-2; //implies there can never be slides.
		} else if (data.length() == 0) {
			return -1;
		}
		return Double.parseDouble(data);
		
	}
	
	public String parseComments() {
		if (rawData.length == 7) {
			String data = rawData[6].trim() + "";
			return data;
		}
		return "";
		
	}
	
	public void procInput(String[] data) {
		if (data.length > 1) {
			if (slides < -1 && data.length == 2) {
				comments = data[1];
			} else if (slides == -1 && data.length == 2) {
				slides = Double.parseDouble(data[1].trim());
			} else {
				slides = Double.parseDouble(data[1].trim());
				comments = data[2];
			}
		}
		reams = Double.parseDouble(data[0].trim());
		
		updateRawData();
	}
	
	public void updateRawData() {
		String paper = reams + "";
		String plastic = slides + "";
		rawData[1] = s(rawData[1].length() - paper.length() - 2) + paper;
		if (slides > -1) {
			rawData[2] = s(rawData[2].length() - plastic.length() - 2) + plastic;
		}
		
	}
	
	public boolean isComplete() {
		return reams > -1;
	}
	
	private String s(int count){
		String ret = "";
		for (int i = 0; i < count; i++) {
			ret += " ";
		}
		return ret;
	}
	
	public String toString() {
		String ret = "";
		for (int i = 0; i < rawData.length-1; i++) {
			ret += rawData[i] + "|";
		}
		ret += " " + comments;
		return ret;
	}

}
