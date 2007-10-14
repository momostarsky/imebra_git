/*
$fileHeader$
*/

/*!

\page imebra_transactions_locks Transactions and common locks

\section imebra_transactions_locks_introduction Introduction

In order to keep the dataSet in a consistent state while several threads
 read and write into it, the following features have been introduced in Imebra:
 - \ref imebra_locks
 - \ref imebra_transactions

A common lock is a mutex shared by several objects; it is used by 
 \ref puntoexe::imebra::dataSet and all its components (\ref puntoexe::imebra::dataGroup and 
 \ref puntoexe::imebra::data objects) and by the \ref puntoexe::imebra::image and 
 its buffer (\ref puntoexe::imebra::buffer).

The transactions objects force the update of several elements in "one go".
This means that when several writing handlers are deallocated, the modifications are
 kept on hold until the transaction object is deallocated; if one of the modifications
 doesn't complete successfully then all the modifications are rolled back and
 the dataSet remains in a consistent state.


\section imebra_locks The common locks

It is used by the dataSet and by the image objects: it is a mutex that is shared 
 by all the objects owned by the dataSet and by the image.
For instance, if when a single tag is locked by using the \ref puntoexe::lockObject
 class then all the dataSet where the tag is contained is also locked, together
 with all the groups and tags contained by the dataSet.

This is useful when an application has to read several tags and has to be
 sure that all the retrieved tags represents that dataSet's status at the same
 moment in time. In order to do this the application must lock the dataSet
 object; this will lock all the groups and the tags contained in the dataSet and
 will ensure that other threads will be paused when they try to modify the
 dataSet.
Once the dataSet has been locked the application can read all the tags and
 rest assured that all of them represents a consistent status of the dataSet.

The shared lock should be released as soon as possible in order to minimize
 the pause time in the threads that are trying to access to the dataSet.


\section imebra_transactions The transactions

The application can include several dataSets update in one or more nested
 transactions: if one of the updates included in one transaction fails then
 all the updates included in the same transaction are rolled back.

A single transaction can involve updates on different dataSets.

Imebra provides two kind of transactions:
- committing transactions
- non-committing transactions

A committing transaction tries to commits all the changes made to the tags when the
 transaction is closed, while a non-committing transaction delegates the commit to the 
 parent transaction; this means that only a nested transaction can be a non-committing 
 transaction and Imebra will always create a committing transaction for non nested ones.

In order to include one or more write operations in a transaction the application has to
 enclose them in a transaction block. A transaction block is initiated by the macro
 IMEBRA_TRANSACTION_START() or IMEBRA_COMMIT_TRANSACTION_START() and is terminated by
 the macro IMEBRA_TRANSACTION_END().

For instance, the following code tries to write a value in the tags 0010,0010 
 (patient's name) and 0010,1010 (patient's age). If an error occurs inside the
 transaction block then both the tags will retain their initial value.

\code
using namespace puntoexe;
// Create the dataset and setup the charset
ptr<imebra::dataSet> myDataSet(new dataSet);
imebra::tCharsetsList myCharsets;
myCharsets.push_back(L"ISO_IR 192"); // UTF-8
myDataSet->setCharsetsList(&myCharsets);

// Write the initial values in the
myDataSet->setUnicodeString(0x0010, 0, 0x0010, 0, L"Initial^name");
myDataSet->setUnsignedLong(0x0010, 0, 0x1010, 0, 10); // ten years old

IMEBRA_TRANSACTION_START();
// If an error occurs here then the two tags will retail their
//  initial state
myDataSet->setUnicodeString(0x0010, 0, 0x0010, 0, L"Surname^name");
myDataSet->setUnsignedLong(0x0010, 0, 0x1010, 0, 20); // twenty years old

// The values have not been written yet, only when the transaction
//  commits them they will be transferred into the dataset
IMEBRA_TRANSACTION_END();

// The transaction wrote the new values in the dataset.
// If an error occurred during the transaction, an exception
//  has been thrown and must be handled.
\endcode
 




*/