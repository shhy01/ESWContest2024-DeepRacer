///////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, Adaptive Application Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : controldata.cpp
/// SOFTWARE COMPONENT NAME           : ControlData
/// GENERATED DATE                    : 2024-11-01 13:31:52
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "calc/aa/port/controldata.h"

namespace deepracer
{
    namespace service
    {
        namespace controldata
        {
            namespace skeleton
            {

                SvControlDataSkeletonImpl::SvControlDataSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
                    : SvControlDataSkeleton(instanceSpec, mode), m_logger(ara::log::CreateLogger("CALC", "PORT", ara::log::LogLevel::kVerbose))
                {
                }

            } /// namespace skeleton
        } /// namespace controldata
    } /// namespace service
} /// namespace deepracer

namespace calc
{
    namespace aa
    {
        namespace port
        {

            ControlData::ControlData()
                : m_logger(ara::log::CreateLogger("CALC", "PORT", ara::log::LogLevel::kVerbose)), m_running{false}, m_CEventData{0U, 0U, 0U}
            {
            }

            ControlData::~ControlData()
            {
            }

            void ControlData::Start()
            {
                m_logger.LogVerbose() << "ControlData::Start";

                // construct skeleton
                ara::core::InstanceSpecifier specifier{"Calc/AA/ControlData"};
                m_interface = std::make_shared<deepracer::service::controldata::skeleton::SvControlDataSkeletonImpl>(specifier);

                // offer service
                auto offer = m_interface->OfferService();
                if (offer.HasValue())
                {
                    m_running = true;
                    m_logger.LogVerbose() << "ControlData::Start::OfferService";
                }
                else
                {
                    m_running = false;
                    m_logger.LogError() << "ControlData::Start::OfferService::" << offer.Error().Message();
                }
            }

            void ControlData::Terminate()
            {
                m_logger.LogVerbose() << "ControlData::Terminate";

                // stop port
                m_running = false;

                // stop offer service
                m_interface->StopOfferService();
                m_logger.LogVerbose() << "ControlData::Terminate::StopOfferService";
            }

            void ControlData::WriteDataCEvent(const deepracer::service::controldata::skeleton::events::CEvent::SampleType &data)
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_CEventData = data;
            }

            void ControlData::SendEventCEventCyclic()
            {
                while (m_running)
                {
                    {
                        std::lock_guard<std::mutex> lock(m_mutex);
                        auto send = m_interface->CEvent.Send(m_CEventData);
                        if (send.HasValue())
                        {
                            m_logger.LogVerbose() << "ControlData::SendEventCEventCyclic::Send";
                        }
                        else
                        {
                            m_logger.LogError() << "ControlData::SendEventCEventCyclic::Send::" << send.Error().Message();
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }

            void ControlData::SendEventCEventTriggered()
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                auto send = m_interface->CEvent.Send(m_CEventData);
                if (send.HasValue())
                {
                    m_logger.LogVerbose() << "ControlData::SendEventCEventTriggered::Send";
                }
                else
                {
                    m_logger.LogError() << "ControlData::SendEventCEventTriggered::Send::" << send.Error().Message();
                }
            }

            void ControlData::SendEventCEventTriggered(const deepracer::service::controldata::skeleton::events::CEvent::SampleType &data)
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_CEventData = data;
                auto send = m_interface->CEvent.Send(m_CEventData);
                if (send.HasValue())
                {
                    m_logger.LogVerbose() << "ControlData::SendEventCEventTriggered::Send";
                }
                else
                {
                    m_logger.LogError() << "ControlData::SendEventCEventTriggered::Send::" << send.Error().Message();
                }
            }

        } /// namespace port
    } /// namespace aa
} /// namespace calc

/// EOF