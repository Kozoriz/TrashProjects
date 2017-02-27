#include "drone_message_handler/drone_message_handler_impl.h"
namespace drone_message_handler {
DroneMessageHandlerImpl::DroneMessageHandlerImpl(const utils::Profile &settings) : settings_(settings) {}
DroneMessageHandlerImpl::~DroneMessageHandlerImpl() {}

void DroneMessageHandlerImpl::Run()
{

}

void DroneMessageHandlerImpl::Join()
{

}

void DroneMessageHandlerImpl::SendMessageToDroid(const messages::Message *message)
{
    messages_to_client_.PushMessage(message);
}

void DroneMessageHandlerImpl::set_socket(utils::SocketServer *socket)
{
    socket_ = socket;
}
}
