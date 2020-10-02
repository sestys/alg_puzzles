import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;


public class Hartals {

    private static List<Integer> dayID = new ArrayList<>();
    private static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int testCases = sc.nextInt();
        int days, parties, hartal, strike;
        // each test case
        for(int i =0; i< testCases; i++){
            days = sc.nextInt();
            parties = sc.nextInt();
            //go throw each party, add days, on which day will strike
            for(int j = 0; j< parties; j++){
                hartal = sc.nextInt();
                strike = 0;
                while ((strike += hartal) <= days){
                    if ((strike%7 != 0) && (strike%7 != 6)){
                        //if given day is not in the list, add it into
                        if(!dayID.contains(strike)){
                            dayID.add(strike);
                        }
                    }
                }
            }
            System.out.println(dayID.size());
            dayID.clear();
        }

    }

}
