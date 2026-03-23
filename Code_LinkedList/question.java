import java.util.HashSet;
import java.util.List;

public class question {
    
    public class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) { this.val = val; }
        ListNode(int val, ListNode next) { this.val = val; this.next = next; }
    }

    //leetcode 876 (midlle element)  gives middle node if size is odd otherwise gives upperBound node if size is even 
    public ListNode middleNode(ListNode head) {
        if(head == null || head.next == null)   return head;

        ListNode slow = head;
        ListNode fast = head;

        while(fast != null && fast.next != null)
        {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        return slow;
    }

    //leetcode 206 (reverse ll)
    public ListNode reverseList(ListNode head) {
        if(head == null || head.next == null)   return head;

        ListNode curr = head;
        ListNode prev = null;
        while(curr != null)
        {
            ListNode fwd = curr.next;
            curr.next = prev;
            prev = curr;
            curr = fwd;
        }
        return prev;
    }
    
    //gives middle node if size is odd otherwise gives lowerBound node if size is even 
    public ListNode getMiddleNode(ListNode head) {
        if(head == null || head.next == null)   return head;

        ListNode slow = head;
        ListNode fast = head;

        while(fast.next != null && fast.next.next != null)
        {
            slow = slow.next;
            fast = fast.next.next;
        }
        
        return slow;
    }

    //Question - reverse the data of linked list 
    public ListNode reverseListData(ListNode head)
    {
        if(head == null || head.next == null)   return head;

        ListNode midNode = getMiddleNode(head);
        ListNode nHead = midNode.next;
        midNode.next = null;

        nHead = reverseList(nHead);
        ListNode curr = head;
        ListNode curr1 = nHead;

        while(curr!=null && curr1!=null)
        {
            int data = curr.val;
            curr.val = curr1.val;
            curr1.val = data;

            curr = curr.next;
            curr1 = curr1.next;
        }

        nHead = reverseList(nHead);
        midNode.next = nHead;

        return head;
    }

    //leetcode 234
    public boolean isPalindrome(ListNode head) {

        if(head == null || head.next == null)   return true;
        
        ListNode midNode = getMiddleNode(head);
        ListNode nHead = midNode.next;
        midNode.next = null;

        nHead = reverseList(nHead);
        ListNode curr = head, curr1 = nHead;

        boolean flag = true;
        while(curr!=null && curr1!=null)
        {
            if(curr.val != curr1.val)
            {
                flag = false;
                break;
            }
            
            curr = curr.next;
            curr1 = curr1.next;
        }

        nHead = reverseList(nHead);
        midNode.next = nHead;

        return flag;
    }

    //leetcode 203
    public ListNode removeElements(ListNode head, int val) {
        if(head==null)  return head;
        ListNode temp = new ListNode(-1,head);
        
        ListNode curr = temp;
        
        while(curr.next != null)
        {
            if(curr.next.val == val)
                curr.next = curr.next.next;
            else
                curr = curr.next;
        }
        
        return temp.next;
    } 

    //leetcode 83
    public ListNode deleteDuplicates(ListNode head) {
        ListNode curr = head;
        
        while(curr!=null)
        {
            if(curr.next != null && curr.next.val == curr.val)
                curr.next = curr.next.next;
            else
                curr = curr.next;
        }
        return head;
    }

    //leetcode 19
    public ListNode removeNthFromEnd(ListNode head, int n) {
        if(head == null || n<=0)    return null;
        if(head.next == null && n==1)   return null;

        ListNode slow = head, fast = head;

        while(n-- > 0)
        {
            fast = fast.next;
            // if(fast == null && n>0) return head;
        }

        if(fast==null)  return slow.next;

        while(fast.next!=null)
        {
            slow = slow.next;
            fast = fast.next;
        }

        ListNode fwd = slow.next;
        slow.next = slow.next.next;
        fwd.next = null;

        return head;
    }
    
    //leetcode 143
    public void reorderList(ListNode head) {
        if(head == null || head.next == null || head.next.next==null)   return;
        
        ListNode midNode = getMiddleNode(head);
        ListNode nHead = midNode.next;
        midNode.next = null;

        nHead = reverseList(nHead);
        ListNode curr1 = head, curr2 = nHead;
        while(curr1 != null && curr2 != null)
        {
            ListNode fwd1 = curr1.next, fwd2 = curr2.next;
            curr1.next = curr2;
            curr2.next = fwd1;

            curr1 = fwd1;
            curr2 = fwd2;
        }
    }

    //Question - change the reordered list to its original form
    //solution - SIMILAR to leetcode 328 (odd even linked list)


    //leetcode 21
    public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if(l1 == null || l2 == null)
            return (l1==null)?l2:l1;
        
        ListNode head = new ListNode(-1);
        ListNode prev = head;

        ListNode curr1 = l1, curr2 = l2;
        
        while(curr1 != null && curr2 != null)
        {
            if(curr1.val <= curr2.val)
            {
                prev.next = curr1;
                prev = curr1;
                curr1 = curr1.next;
            }
            else{
                prev.next = curr2;
                prev = curr2;
                curr2 = curr2.next;
            }
        }

        if(curr1!=null)
            prev.next = curr1;
        else if(curr2!=null)
            prev.next = curr2;

        return head.next;
    }

    //leetcode 328
    public ListNode oddEvenList(ListNode head) {

        if(head== null || head.next == null || head.next.next == null)  return head;

        ListNode curr1 = head, curr2 = head.next, nHead = head.next;

        while(curr1.next != null && curr2.next != null)
        {
            curr1.next = curr2.next;
            curr1 = curr2.next;

            curr2.next = curr1.next;
            curr2 = curr1.next;
        }

        curr1.next = nHead;
        return head;
    }

    //leetcode 2
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode ans = new ListNode(0);
        ListNode p = l1, q = l2, curr = ans;
        int carry = 0;
        while (p != null || q != null) {
            int x = (p != null) ? p.val : 0;
            int y = (q != null) ? q.val : 0;
            int sum = carry + x + y;
            carry = sum / 10;
            curr.next = new ListNode(sum % 10);
            curr = curr.next;
            if (p != null) p = p.next;
            if (q != null) q = q.next;
        }
        if (carry > 0) {
            curr.next = new ListNode(carry);
        }
        return ans.next;
    }

    //leetcode 141
    public boolean hasCycle(ListNode head) {
        if(head == null || head.next == null)
            return false;

        ListNode slow = head, fast = head;

        while(fast != null && fast.next != null)
        {
            slow = slow.next;
            fast = fast.next.next;
            if(slow == fast)
                return true;
        }

        return false;
    }

    //leetcode 142
    public ListNode detectCycle(ListNode head) {
        if(head == null || head.next == null)
            return null;

        ListNode slow = head, fast = head;

        while(fast != null && fast.next != null)
        {
            slow = slow.next;
            fast = fast.next.next;
            if(fast == slow)
                break;
        }

        if(slow!=fast)
            return null;

        slow = head;
        while(slow!=fast)
        {
            slow = slow.next;
            fast = fast.next;
        }

        return slow;
    }

    //leetcode 445
    public ListNode addTwoNumbers2(ListNode l1, ListNode l2) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);

        if(l1 == null || l2 == null)
            return (l1!=null)?l1:l2;

        int carry = 0;
        ListNode ans = new ListNode(-1);
        ListNode curr = ans, p = l1, q = l2;

        while(p !=null || q != null)
        {
            int x = (p!=null)?p.val:0;
            int y = (q!=null)?q.val:0;
            int sum = x+y+carry;
            carry = sum/10;
            curr.next = new ListNode(sum%10);
            curr = curr.next;
            if(p!=null) p = p.next;
            if(q!=null) q = q.next;
        }

        if(carry>0)
            curr.next = new ListNode(carry);
        
        ans = ans.next;
        ans = reverseList(ans);
        return ans;
    }

    //leetcode 82
    public ListNode deleteDuplicates2(ListNode head) {
        if(head == null || head.next == null)
            return head;

        ListNode temp = new ListNode(-1);
        temp.next = head;
        ListNode curr = temp;
        while(curr.next != null && curr.next.next != null)
        {
            if(curr.next.val == curr.next.next.val)
            {
                int val = curr.next.val;
                while(curr.next!=null && curr.next.val==val)
                {
                    curr.next = curr.next.next;
                }
            }
            else {
                curr = curr.next;
            }
        }
        return temp.next;
    }

    //leetcode 92
    ListNode th = null, tt = null;      //temp head, temp tail
    public void addFirst(ListNode node)
    {
        if(th == null)
        {
            th = node;
            tt = node;
        }else{
            node.next = th;
            th = node;
        }
    }

    public ListNode reverseBetween(ListNode head, int m, int n) {
        if(head == null || head.next == null || m==n)
            return head;

        ListNode nHead = head;
        ListNode curr = head;
        ListNode prev = null;
        int idx = 1;

        while(curr!=null)
        {
            while(idx>=m && idx<=n)
            {
                ListNode fwd = curr.next;
                curr.next = null;
                addFirst(curr);

                curr = fwd;
                idx++;
            }

            if(tt!=null)
            {
                tt.next = curr;
                if(prev!=null)
                    prev.next = th;
                else    
                    nHead = th;
                break;
            }

            prev = curr;
            curr = curr.next;
            idx++;
        }

        return nHead;
    }


    //leetcode 160
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if(headA == null || headB == null)
            return null;

        if(headA.next == null && headB.next == null)
            if(headA!=headB)
                return null;
            else   
                return headA;

        ListNode curr = headA;
        while(curr.next!=null)
            curr = curr.next;
        
        curr.next = headA;
        ListNode in = detectCycle(headB);
        curr.next = null;

        return in;
    }

    //leetcode 148
    public ListNode sortList(ListNode head) {
        if(head == null || head.next == null)
            return head;

        ListNode mid = getMiddleNode(head);
        ListNode nHead = mid.next;
        mid.next = null;

        return mergeTwoLists(sortList(head), sortList(nHead));
    }

    //leetcode 23
    public ListNode mergeKLists_(ListNode[] lists, int si, int ei) {
        if(si == ei)
            return lists[si];
        if(si + 1 == ei)
            return mergeTwoLists(lists[si], lists[ei]);

        int mid = (si+ei)>>1;
        
        return mergeTwoLists(mergeKLists_(lists, si, mid), mergeKLists_(lists, mid+1, ei)); 
    }

    public ListNode mergeKLists(ListNode[] lists) {
        int size = lists.length;
        if(size == 0)   return null;
        return mergeKLists_(lists, 0, size-1);
    }


//leetcode 25
ListNode oh = null, ot = null;
public int len(ListNode head)
{
    int l = 0;
    while(head != null)
    {
        ++l;
        head = head.next;
    }
    return l;
}
public ListNode reverseKGroup(ListNode head, int k) 
{
    if(head == null || head.next == null || k==0 || k==1)
        return head;

    ListNode curr = head;

    int l = len(head);
    if(l<k)
        return head;

    while(curr != null)
    {
        int tk = k;
        while(tk-- > 0)
        {
            ListNode fwd = curr.next;
            curr.next = null;
            addFirst(curr);

            curr = fwd;
        }
        l-=k;

        if(ot == null)
        {
            oh = th;
            ot = tt;
        } 
        else
        {
            ot.next = th;
            ot = tt;
        }
        th = tt = null;
        if(l<k)
        {
            ot.next = curr;
            curr = null;
        }
    }
    return oh;
    }
}



