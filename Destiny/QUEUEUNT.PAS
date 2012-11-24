Unit QueueUnt;




INTERFACE

TYPE

  QueueElementType  = RECORD
     top: integer;
     bottom: integer;
    end;  (* or whatever goes in queue  *)

  QueuePtrType = ^QueueNodeType;

  QueueNodeType = RECORD
    Info : QueueElementType; (* the queue user's data      *)
    Next : QueuePtrType      (* pointer to next queue node *)
  END; (* QueueNodeType *)

  QueueType = RECORD
    QFront : QueuePtrType;      (* accesses front of queue *)
    QRear  : QueuePtrType       (* accesses rear of queue  *)
  END;   (* QueueType *)

PROCEDURE CreateQueue
  (VAR Queue : QueueType);
FUNCTION EmptyQueue
  (Queue : QueueType) : Boolean;
FUNCTION FullQueue
  (Queue : QueueType) : Boolean;
PROCEDURE Enqueue
  (VAR Queue  : QueueType;
   NewElement : QueueElementType);
PROCEDURE Dequeue
  (VAR Queue      : QueueType;
   VAR DeqElement : QueueElementType);
PROCEDURE DestroyQueue
  (VAR Queue : QueueType);
{****}
IMPLEMENTATION
{****}

{TYPE

  QueueElementType  = Integer;  (* or whatever goes in queue  *)

  QueuePtrType = ^QueueNodeType;

  QueueNodeType = RECORD
    Info : QueueElementType; (* the queue user's data      *)
    Next : QueuePtrType      (* pointer to next queue node *)
  END; (* QueueNodeType *)

  QueueType = RECORD
    QFront : QueuePtrType;      (* accesses front of queue *)
    QRear  : QueuePtrType       (* accesses rear of queue  *)
  END;   (* QueueType *)
                           }
(***********************************************************)

PROCEDURE CreateQueue
  (VAR Queue : QueueType);

  (* Initializes Queue to an empty state. *)

BEGIN (* CreateQueue *)
  Queue.QFront  := NIL;
  Queue.QRear   := NIL
END; (* CreateQueue *)

(***************************************************************)

FUNCTION EmptyQueue
  (Queue : QueueType) : Boolean;

  (* Returns True if Queue does not contain any elements; *)
  (* returns False otherwise.                             *)

BEGIN (* EmptyQueue *)
  EmptyQueue := (Queue.QFront = NIL)
END; (* EmptyQueue *)

(**************************************************************)

FUNCTION FullQueue
  (Queue : QueueType) : Boolean;

  (* Stub for FullQueue operation. *)

BEGIN (* FullQueue *)
  FullQueue := False
END; (* FullQueue *)

(*********************************************************)

PROCEDURE Enqueue
  (VAR Queue  : QueueType;
   NewElement : QueueElementType);

  (* Adds NewElement to the rear of Queue. Assumes that *)
  (* Queue is not "full."                               *)

VAR
  NewNode : QueuePtrType;

BEGIN (* Enqueue *)

  (* Create a node for the new element. *)
  New (NewNode) ;
  NewNode^.Info  := NewElement;
  NewNode^.Next := NIL;

  (* Insert new node at rear of Queue. *)
  IF Queue.QRear = NIL (* queue is empty *)
    THEN Queue.QFront := NewNode
    ELSE Queue.QRear^.Next := NewNode;

  (* Update external pointer to rear of Queue. *)
  Queue.QRear := NewNode

END; (* Enqueue *)

(***************************************************)

PROCEDURE Dequeue
  (VAR Queue      : QueueType;
   VAR DeqElement : QueueElementType);

  (* Removes front element from Queue and returns its *)
  (* value in DeqElement. Assumes Queue is not empty. *)

VAR
  TempPtr : QueuePtrType;

BEGIN (* Dequeue *)

  TempPtr := Queue.QFront; (* save it for Dispose *)

  (* Take DeqElement from front node of Queue. *)
  DeqElement := Queue.QFront^.Info;

  (* Remove front node from Queue. *)
  Queue.QFront := Queue.QFront^.Next;
  IF Queue.QFront = NIL (* queue is empty *)
    THEN Queue.QRear := NIL;

  Dispose (TempPtr)

END; (* Dequeue *)

(******************************************************)

PROCEDURE DestroyQueue
  (VAR Queue : QueueType);

VAR
  TempPtr : QueuePtrType;

BEGIN (* DestroyQueue *)

  WHILE Queue.QFront <> NIL DO
    BEGIN
      TempPtr := Queue.QFront;
      Queue.QFront := Queue.QFront^.Next;
      Dispose (TempPtr)
    END; (* WHILE *)

  Queue.QRear := NIL

END;  (* DestroyQueue *)

(****************************************************************)
end.