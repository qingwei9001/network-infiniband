#pragma once
#include "../../common/Packet.h"
#include <boost/serialization/array.hpp>

namespace hiveNetworkCommon
{
	class CLogicalNode;
}

class CTestPacket : public hiveNetworkCommon::IUserPacket
{
public:
	CTestPacket(void);
	CTestPacket(const std::string& vSig);
	~CTestPacket(void);

	virtual void processV(hiveNetworkCommon::CLogicalNode *vHostNode) override;

private:
	unsigned char* m_pData;

	template<class TArchieve>
	void serialize(TArchieve& vAr, const unsigned int vVersion)
	{
		vAr & boost::serialization::base_object<hiveNetworkCommon::IUserPacket>(*this);
		if (!m_pData) m_pData = new unsigned char[1024*768*4];
		vAr & boost::serialization::make_array(m_pData, 1024*768*4);	
	}

	friend class boost::serialization::access;
};