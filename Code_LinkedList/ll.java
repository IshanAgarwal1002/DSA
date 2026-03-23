public class ll {
    
    public static class linkedlist{

        public class Node{

            int data;
            Node next;

            Node(int data)
            {
                this.data = data;
                next = null;
            }
        }

        Node head;
        Node tail;
        int size;

        linkedlist(){
            head = null;
            tail = null;
            size = 0;
        }

        public int size()
        {
            return this.size();
        }

        public boolean isEmpty()
        {
            return size==0;
        }

        public void display()
        {
            if(isEmpty())
            {
                System.out.println("Empty");
                return;
            }
            Node curr = head;
            while(curr != null){
                System.out.print(curr.data + " -> ");
                curr = curr.next;
            }
        }

        //insertion=======================================
        private void addFirstNode(Node node)
        {
            if(size==0)
            {
                head = tail = node;
            }else{
                node.next = head;
                head = node;
            }
            size++;
        }

        public void addFirst(int data)
        {
            Node node = new Node(data);
            addFirstNode(node);
        }

        private void addLastNode(Node node)
        {
            if(size==0)
            {
                head = tail = node;
            }else{
                tail.next = node;
                tail = node;
            }
            size++;
        }

        public void addLast(int data)
        {
            Node node = new Node(data);
            addLastNode(node);
        }

        private void addAtNode(Node node, int pos)
        {
            if(pos == 0)
                addFirstNode(node);
            else if(pos == size)
                addLastNode(node);
            else{
                Node prevNode = getAt(pos-1);
                Node temp = prevNode.next;

                prevNode.next = node;
                node.next = temp;
            }
            size++;
        }

        public void addAt(int data, int pos)
        {
            Node node = new Node(data);
            addAtNode(node,pos);
        }

        //retrieval============================================

        public Node getFirst()
        {
            if(isEmpty())
            {
                System.out.println("Empty List");
                return null;
            }
            return head;
        }

        public Node getLast()
        {
            if(isEmpty())
            {
                System.out.println("Empty List");
                return null;
            }
            return tail;
        }

        public Node getAt(int pos)
        {
            if(pos<0 || pos>=size)
            {
                System.out.println("Null pointer exception.");
                return null;
            }
            Node curr = head;
            while(pos-- > 0)
                curr = curr.next;   
            
            return curr;
        }

        //deletion=============================================
        public void removeFirst()
        {
            if(isEmpty()){
                System.out.println("Empty");
                return;
            }
            if(size==1){
                head = tail = null;
            }
            else{
                head = head.next;
            }
            size--;
        }

        public void removeLast()
        {
            if(isEmpty()){
                System.out.println("Empty");
                return;
            }
            if(size==1){
                head = tail = null;
            }
            else{
                Node prev = getAt(size-2);
                prev.next = null;
                tail = prev;
            }
            size--;
        }

        public void removeAt(int pos)
        {
            if(pos<0 || pos>=size){
                System.out.println("Null pointer exception");
                return;
            }
            if(pos == 0)
                removeFirst();
            else if(pos == size-1)
                removeLast();
            else{
                Node prev = getAt(pos-1);
                Node node = prev.next;
                prev.next = node.next;
                node.next = null;
                size--;
            }
        }
    }


    public static void main(String[] args){
        linkedlist ll=new linkedlist();
        for(int i=1;i<10;i++){
            ll.addFirst(i*10);
        }
        for(int i=1;i<10;i++){
            ll.addLast(i*10);
        }

        
        ll.display();
    }
}