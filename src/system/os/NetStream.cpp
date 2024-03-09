#include "os/NetStream.h"
#include "os/Debug.h"
#include "os/Timer.h"

NetStream::NetStream() : BinStream(true), mFail(0), mReadTimeoutMs(0.0f), mBytesRead(0), mBytesWritten(0) {
    mSocket = NetworkSocket::Create(true);
}

NetStream::~NetStream(){
    if(mSocket){
        mSocket->Disconnect();
        delete mSocket;
    }    
}

void NetStream::ClientConnect(const NetAddress& addr){
    MILO_ASSERT(mSocket, 0x37);
    Timer timer;
    timer.Restart();
}

bool NetStream::Eof(){
    return !mSocket->CanRead();
}

void NetStream::SeekImpl(int i, SeekType ty){
    MILO_ASSERT(false, 0x79);
}

int NetStream::ReadAsync(void* v, int i){
    return mSocket->Recv(v, i);
}
