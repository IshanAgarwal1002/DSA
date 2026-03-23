public class Encoding {

    public static void main(String[] args)
    {
        uniqueLetters((str1+str2+str3));

        String str = createString();

        LetterNumMap = new int[26];

        System.out.print(crypto(str, 0));
    }

    static String str1 = "send";
    static String str2 = "more";
    static String str3 = "money";

    static int letters = 0;        //bitArray to store unique letters 
    public static void uniqueLetters(String str)
    {
        for(int i=0;i<str.length();i++)
        {
            int mask = (1 << (str.charAt(i) - 'a'));
            letters |= mask;
        }
    }

    public static String createString()
    {
        String str = "";
        for(int i=0;i<26;i++)
        {
            int mask = (1<<i);
            if((mask & letters) != 0)
                str += (char)(i + 'a');
        }

        return str;
    }

    static int[] LetterNumMap;      //array to map the character against its number code

    public static int StringToNum(String str)
    {
        int n=0;
        for(int i=0;i<str.length();i++)
        {
            n = n*10 + LetterNumMap[str.charAt(i) - 'a'];
        }
        return n;
    }

    static int numUsed = 0;        //bitarray to store if number is used in encoding or not
    public static int crypto(String str, int idx)
    {
        if(idx == str.length())
        {
            int num1 = StringToNum(str1);
            int num2 = StringToNum(str2);
            int num3 = StringToNum(str3);
            if((num1 + num2 == num3) && (LetterNumMap[str1.charAt(0) - 'a'] != 0) && (LetterNumMap[str2.charAt(0) - 'a'] != 0) && (LetterNumMap[str3.charAt(0) - 'a'] != 0))
            {
                System.out.println(num1);
                System.out.println("+" + num2);
                System.out.println("------");
                System.out.println(num3);

                return 1;
            }
            return 0;
        }

        int count = 0;

        for(int num=0;num<=9;num++)
        {
            int mask = (1<<num);
            if((mask & numUsed) == 0)
            {
                numUsed ^= mask;
                LetterNumMap[str.charAt(idx) - 'a'] = num;
                count += crypto(str, idx+1);
                numUsed ^= mask;
                LetterNumMap[str.charAt(idx) - 'a'] = 0;
            }
        }

        return count;
    }
}