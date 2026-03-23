import java.util.Scanner;
import java.util.ArrayList;

public class recursion_basic
{
    public static Scanner input = new Scanner(System.in);

    public static void main(final String[] args) {
        solve();
    }

    public static void solve() {
        // set1();
        // set2();
        set3();
    }

    public static void set1()
    {
        int a = input.nextInt();
        int b = input.nextInt();
        // System.out.println(fact(n));
        System.out.println(power2(a,b));
    }

    public static int fact(int n)
    {
        return n<=1 ? 1 : n*fact(n-1);
    }

    public static int power(int a,int b)
    {
        return (b==0)?1:a*power(a,b-1);
    }

    public static int power2(int a,int b)
    {
        if(a==0)    return 0;
        if(b<=0)    return 1;
        int n = power2(a,b/2);
        n*=n;

        return (b%2==0)?n:n*a;
    }

    //set2=======================================================================

    public static void display(int[] arr,int idx)
    {
        if(idx==arr.length)   return;
        System.out.print(arr[idx] + " ");
        display(arr,idx+1);
    }

    public static boolean find_01(int[] arr,int idx, int data)
    {
        if(idx==arr.length)     return false;
        if(arr[idx]==data)      return true;
        return find_01(arr, idx+1, data);
    }

    public static boolean find_02(int[] arr,int idx, int data)
    {
        if(idx==arr.length)     return false;
        boolean ans=find_02(arr, idx+1, data);
        if(ans) return true;
        else    return arr[idx]==data;
    }

    public static int maximum(int[] arr, int idx)
    {
        if(idx==arr.length-1)     return arr[idx];
        int ans = maximum(arr, idx+1);
        return Math.max(arr[idx],ans);
    }

    public static int minimum(int[] arr, int idx)
    {
        if(idx==arr.length-1)     return arr[idx];
        int ans = minimum(arr, idx+1);
        return Math.min(arr[idx],ans);
    }

    public static int fibo(int n)
    {
        if(n<=1)
            return n;
        return fibo(n-1) + fibo(n-2);
    }

    public static void fibo2(int a,int b,int n)
    {
        if(n==0)
            return;
        System.out.println(a);
        fibo2(b,a+b,n-1);
    }

    public static void set2()
    {
        int[] arr = {-1,234,34,7,2,999,23,4,5,6,3,2,5,7,32};
        // display(arr,0);
        // int n = input.nextInt();
        // System.out.print(find_01(arr,0,n));
        System.out.print(minimum(arr, 0));
    }

    //set3===============================================

    public static ArrayList<String> subsequence1(String str)
    {
        if(str.length()==0)
        {
            ArrayList <String> baseAns = new ArrayList<>();
            baseAns.add(str);
            return baseAns;
        }
        
        char ch = str.charAt(0);
        String nstr = str.substring(1);

        ArrayList <String> ans = subsequence1(nstr);
        int n = ans.size();
        for(int i=0;i<n;i++)
        {
            ans.add(ch+ans.get(i));
        }
        
        return ans; 
    }

    public static int subsequence2(String str,String ans)
    {
        if(str.length() == 0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        char ch = str.charAt(0);
        String nstr = str.substring(1);

        count += subsequence2(nstr,ans);
        count += subsequence2(nstr,ans+ch);

        return count;
    }

    public static ArrayList<String> permutation1(String str)    //duplicacy allowed, return type
    {
        if(str.length()==1)
        {
            ArrayList <String> base = new ArrayList<>();
            base.add(str);
            return base;
        }
        
        char ch = str.charAt(0);
        
        ArrayList <String> ans = permutation1(str.substring(1));
        ArrayList <String> newAns = new ArrayList<>();

        for(String s: ans)
        {
            for(int i=0;i<=s.length();i++)
            {
                newAns.add(s.substring(0,i)+ch+s.substring(i));
            }
        }

        return newAns;
    }

    public static int permutation2(String str,String ans)
    {
        if(str.length()==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;

        for(int i=0;i<str.length();i++)
        {
            char ch = str.charAt(i);
            String nstr = str.substring(0,i) + str.substring(i+1);
            count += permutation2(nstr, ans+ch);
        }

        return count;
    }

    public static int permutation3(String str,String ans)
    {
        if(str.length()==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count = 0;
        boolean[] alpha = new boolean[26];
        for(int i=0;i<str.length();i++)
        {
            char ch = str.charAt(i);
            if(!alpha[ch-'a'])
            {
                alpha[ch-'a'] = true;
                String nstr = str.substring(0,i) + str.substring(i+1);
                count += permutation3(nstr,ans+ch);
            }
        }

        return count;
    }

    public static String[] words = { ":;/", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "&*%", "#@$", "+-=" };

    public static ArrayList <String> nokiaKeypad1(String str)
    {
        if(str.length()==0)
        {
            ArrayList <String> base = new ArrayList<>();
            base.add(str);
            return base;
        }

        int n = str.charAt(0) - '0';
        String word = words[n];
        ArrayList <String> ans = nokiaKeypad1(str.substring(1));
        ArrayList <String> newAns = new ArrayList<>();

        for(String s:ans)
        {
            for(int i=0;i<word.length();i++)
            {
                newAns.add(word.charAt(i)+s);
            }
        }

        return newAns;
    }

    public static int nokiaKeypad2(String str,String ans)
    {
        if(str.length()==0)
        {
            System.out.println(ans);
            return 1;
        }

        int count=0;
        int n = str.charAt(0) - '0';
        String word = words[n];
        
        for(int i=0;i<word.length();i++)
        {
            count += nokiaKeypad2(str.substring(1), ans + word.charAt(i));            
        }

        if(str.length()>1)
        {
            int num = n*10 + (str.charAt(1) - '0');
            if(num==10 || num==11)
            {
                word = words[num];
                for(int i=0;i<word.length();i++)
                {
                    count += nokiaKeypad2(str.substring(2), ans + word.charAt(i));            
                }
            }
        }

        return count;
    }

    public static void set3()
    {
        String str = input.nextLine();
        // System.out.print(subsequence2(str,""));
        // System.out.print(permutation2(str,""));
        // System.out.print(permutation3(str, ""));
        System.out.print(nokiaKeypad2(str,""));
    }
}