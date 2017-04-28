import java.util.Scanner;

public class 最大公因數 {
	
	public static int find( int M, int N ) {
		for( int i = N ; i > 0 ; i-- ) {
			if( N % i == 0 && M % i == 0 ) {
				return i;
			}
		}
		
		return 0; // 0 == error ( 不可能出現公因數 = 0 )
		
	} // find() M > N
	
	public static void main( String[] args ) {
		Scanner input = new Scanner(System.in);
		
		int num1 = input.nextInt();
		int num2 = input.nextInt();
		int ans = 0;
		
		if( num1 > num2 ) {
			ans = find( num1, num2 );
		}
		else if ( num1 < num2 ) {
			ans = find( num2, num1 );
		}
		else{
			ans = num1;
		} // num1 == num2
		
		System.out.printf("%d\n", ans);
		
	} // main()
}
