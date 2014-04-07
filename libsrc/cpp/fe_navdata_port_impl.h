#ifndef FE_NAVDATA_PORT_H
#define FE_NAVDATA_PORT_H

#include "fe_port_impl.h"

#include <redhawk/FRONTEND/NavigationData.h>

namespace frontend {

    class nav_delegation {
        public:
            virtual frontend::NavigationPacket get_nav_packet(const std::string& port_name) = 0;
            virtual void set_nav_packet(const std::string& port_name, const frontend::NavigationPacket &nav_info) = 0;
    };
    // ----------------------------------------------------------------------------------------
    // InNavDataPort declaration
    // ----------------------------------------------------------------------------------------
    class InNavDataPort : public POA_FRONTEND::NavData, public Port_Provides_base_impl
    {
        public:
            InNavDataPort(std::string port_name, nav_delegation *_parent) : 
            Port_Provides_base_impl(port_name)
            {
                parent = _parent;
            };
            ~InNavDataPort() {};
            
            FRONTEND::NavigationPacket* nav_packet() {
                boost::mutex::scoped_lock lock(portAccess);
                frontend::NavigationPacket retval = this->parent->get_nav_packet(this->name);
                FRONTEND::NavigationPacket* tmpVal = frontend::returnNavigationPacket(retval);
                return tmpVal;
            };
            void nav_packet(const FRONTEND::NavigationPacket &gps) {
                boost::mutex::scoped_lock lock(portAccess);
                frontend::NavigationPacket input = frontend::returnNavigationPacket(gps);
                this->parent->set_nav_packet(this->name, input);
                return;
            };
            
        protected:
            nav_delegation *parent;
            boost::mutex portAccess;
    };
    
    // ----------------------------------------------------------------------------------------
    // OutNavDataPort declaration
    // ----------------------------------------------------------------------------------------
    template<typename PortType_var, typename PortType>
    class OutNavDataPortT : public OutFrontendPort<PortType_var,PortType>
    {
        public:
            OutNavDataPortT(std::string port_name) : OutFrontendPort<PortType_var, PortType>(port_name)
            {};
            ~OutNavDataPortT(){};
            
            frontend::NavigationPacket nav_packet() {
                frontend::NavigationPacket retval;
                std::vector < std::pair < FRONTEND::NavData_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            const FRONTEND::NavigationPacket_var tmp = ((*i).first)->nav_packet();
                            retval = frontend::returnNavigationPacket(tmp);
                        } catch(...) {
                        }
                    }
                }
                return retval;
            };
            void nav_packet(const frontend::NavigationPacket &nav) {
                std::vector < std::pair < FRONTEND::NavData_var, std::string > >::iterator i;
                boost::mutex::scoped_lock lock(this->updatingPortsLock);   // don't want to process while command information is coming in
                if (this->active) {
                    for (i = this->outConnections.begin(); i != this->outConnections.end(); ++i) {
                        try {
                            const FRONTEND::NavigationPacket tmp = frontend::returnNavigationPacket(nav);
                            ((*i).first)->nav_packet(tmp);
                        } catch(...) {
                        }
                    }
                }
                return;
            };
    };
    class OutNavDataPort : public OutNavDataPortT<FRONTEND::NavData_var,FRONTEND::NavData> {
        public:
            OutNavDataPort(std::string port_name) : OutNavDataPortT<FRONTEND::NavData_var,FRONTEND::NavData>(port_name)
            {};
    };
    
} // end of frontend namespace


#endif
