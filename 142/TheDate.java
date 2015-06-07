public class Date {
	
	private int month;
	private int day;
	
	public Date(int theMonth, int theDay) {
		day = theDay;
		month = theMonth;
	}
	
	public int getMonth() {
		return month;
	}
	
	public int getDay() {
		return day;
	}
	
	public void setDate(int theMonth, int theDay) {
		month = theMonth;
		day = theDay;
	}
	
	public boolean equals(Date d) {
		return (d.month == this.month && d.day == this.day);
	}
	
	public int daysInMonth() {
		if (month == 2) {
			return 28;
		} else if ((month % 2 == 1 && month <= 7) || (month % 2 == 0 && month >= 8)) {
			return 31;
		} else { 
			return 30;
		}	
	}
	
	public void nextDay() {
		if (day < this.daysInMonth()) {
			day++;
		} else if (month < 12) {
			month++;
			day = 1;
		} else {
			month = 1;
			day = 1;
		}
	}
	
	public String toString() {
		return month + "/" + day;
	}
	

}
