#ifndef BTPROXY_SDP_H
#define BTPROXY_SDP_H

void bpsdp_init();
void bpsdp_run();
extern void btproxy_sdp_early_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);

#ifdef INCLUDING_FROM_SDP_C
static void bpsdp_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size)
{
	// filter based on channel, prepare the proper service record according to channel
	btproxy_sdp_early_packet_handler(packet_type, channel, packet, size);
	// then call the actual sdp service
	sdp_packet_handler(packet_type, channel, packet, size);
}

void bpsdp_init()
{
	l2cap_register_service_internal(NULL, bpsdp_packet_handler, PSM_SDP, 0xffff, LEVEL_0);
}

void bpsdp_run()
{
	sdp_try_respond();
}

#endif

#endif
