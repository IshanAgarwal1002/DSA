public class Coins
{
    public static void main(final String[] args) {
            // int[] arr={2,3,5,7};
            int[] arr={1,1,1,1,1};
            int tar=3;
            int ans=0;
            boolean[] vis=new boolean[arr.length];
            // ans=coinChangePermuINFI_01(arr,tar,"");
            ans=coinChangePermu_01(arr,tar,vis,"");
    
            // ans=coinChangeCombinationINFI_01(arr,0,tar,"");
            // ans=coinChangeCombination_01(arr,0,tar,"");
    
    
            // ans=coinChangePermuINFI_02(arr,0,tar,"");
    
            // ans=coinChangeCombinationINFI_02(arr,0,tar,"");
            // ans=coinChangeCombination_02(arr,0,tar,"");
    
            System.out.println(ans);
    
        }

    public static int coinChangePermuINFI_01(int[] arr,int tar,String ans){
        if(tar==0){
            System.out.println(ans);
            return 1;
        }

        int count=0;
        for(int i=0;i<arr.length;i++){
            if(tar-arr[i]>=0)
             count+=coinChangePermuINFI_01(arr,tar-arr[i],ans + arr[i]+ " ");
        }

        return count;
    }

    public static int coinChangePermu_01(int[] arr,int tar,boolean[] vis,String ans){
        if(tar==0){
            System.out.println(ans);
            return 1;
        }

        int count=0;
        for(int i=0;i<arr.length;i++){
            if(!vis[i] && tar-arr[i]>=0){
                vis[i]=true;
                count+=coinChangePermu_01(arr,tar-arr[i],vis,ans + i+ " ");
                vis[i]=false;
            }
        }
        return count;
    }

    public static int coinChangeCombinationINFI_01(int[] arr,int idx,int tar,String ans){
        if(tar==0){
            System.out.println(ans);
            return 1;
        }

        int count=0;
        for(int i=idx;i<arr.length;i++){
            if(tar-arr[i]>=0)
             count+=coinChangeCombinationINFI_01(arr,i,tar-arr[i],ans + arr[i]+ " ");
        }

        return count;
    }

    public static int coinChangeCombination_01(int[] arr,int idx,int tar,String ans){
        if(tar==0){
            System.out.println(ans);
            return 1;
        }

        int count=0;
        for(int i=idx;i<arr.length;i++){
            if(tar-arr[i]>=0)
             count+=coinChangeCombination_01(arr,i+1,tar-arr[i],ans + arr[i]+ " ");
        }

        return count;
    }

    public static int coinChangeCombination_02(int[] arr,int idx,int tar,String ans){
        if(idx==arr.length || tar==0){
           if(tar==0) 
           {
             System.out.println(ans);
             return 1; 
           }

           return 0;
        }

       int count=0;
       if(tar-arr[idx]>=0)
          count+=coinChangeCombination_02(arr,idx+1,tar-arr[idx],ans+ arr[idx]+ " ");
       count+=coinChangeCombination_02(arr,idx+1,tar,ans);
       
       return count;
   }

   public static int coinChangeCombinationINFI_02(int[] arr,int idx,int tar,String ans){
       if(idx==arr.length || tar==0){
           if(tar==0) 
           {
             System.out.println(ans);
             return 1; 
           }

           return 0;
        }

       int count=0;
       if(tar-arr[idx]>=0)
          count+=coinChangeCombinationINFI_02(arr,idx,tar-arr[idx],ans+ arr[idx]+ " ");
       count+=coinChangeCombinationINFI_02(arr,idx+1,tar,ans);
       
       return count;
   }

   public static int coinChangePermuINFI_02(int[] arr,int idx,int tar,String ans){
       if(idx==arr.length || tar==0){
           if(tar==0) 
           {
             System.out.println(ans);
             return 1; 
           }

           return 0;
        }

       int count=0;
       if(tar-arr[idx]>=0)
          count+=coinChangePermuINFI_02(arr,0,tar-arr[idx],ans+ arr[idx]+ " ");
       count+=coinChangePermuINFI_02(arr,idx+1,tar,ans);
       
       return count;
   }

   public static int coinChangePermu_02(int[] arr,boolean[] vis,int idx,int tar,String ans){
       if(idx==arr.length || tar==0){
           if(tar==0) 
           {
             System.out.println(ans);
             return 1; 
           }

           return 0;
        }

       int count=0;
       if(tar-arr[idx]>=0 && !vis[idx]){
           vis[idx]=true;
           count+=coinChangePermu_02(arr,vis,0,tar-arr[idx],ans+ arr[idx]+ " ");
           vis[idx]=false;
       }
       
       count+=coinChangePermu_02(arr,vis,idx+1,tar,ans);
       
       return count;
   }

}