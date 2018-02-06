// difference is in milliseconds
long diffSeconds = 1000; // compute difference in seconds
long diffMinutes = (60 * 1000); // compute difference in minutes
long diffHours = (60 * 60 * 1000);// compute difference in hours
long diffDays = (24 * 60 * 60 * 1000); // compute difference in days
// Difference between dates (Never use Date class)
// January, 1st, 2012
GregorianCalendar c1 = new GregorianCalendar(2012, 0, 1);
// March, 3rd, 1912
GregorianCalendar c2 = new GregorianCalendar(1912, 2, 3);
long differenceInSeconds =
(c1.getTimeInMillis() - c2.getTimeInMillis()) / {someDiff}; //
 // Sum days to the given date
Calendar calendar = Calendar.getInstance();
calendar.setTime(year, month, day); //Initial date
calendar.add(Calendar.DAY_OF_YEAR, x); //adding or subtracting x days
calendar.getTime(); // Returns a Date instance
