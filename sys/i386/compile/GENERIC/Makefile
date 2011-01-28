KERN_IDENT=GENERIC
DEBUG=-g
# Makefile.i386 -- with config changes.
# Copyright 1990 W. Jolitz
#	from: @(#)Makefile.i386	7.1 5/10/91
# $FreeBSD: src/sys/conf/Makefile.i386,v 1.273.10.1.2.1 2009/10/25 01:10:29 kensmith Exp $
#
# Makefile for FreeBSD
#
# This makefile is constructed from a machine description:
#	config machineid
# Most changes should be made in the machine description
#	/sys/i386/conf/``machineid''
# after which you should do
#	 config machineid
# Generic makefile changes should be made in
#	/sys/conf/Makefile.i386
# after which config should be rerun for all machines.
#

# Which version of config(8) is required.

STD8X16FONT?=	iso

.if !defined(S)
.if exists(./@/.)
S=	./@
.else
S=	../../..
.endif
.endif
.include "$S/conf/kern.pre.mk"

MACHINE=i386

MKMODULESENV+=	MACHINE=${MACHINE}

BEFORE_DEPEND=acpi_quirks.h aic7xxx_seq.h aic7xxx_reg.h \
	aic79xx_seq.h aic79xx_reg.h miidevs.h pccarddevs.h \
	teken_state.h usbdevs.h usbdevs_data.h \
	acpi_wakecode.h 

OBJS=aic7xxx_reg_print.o aic79xx_reg_print.o cam.o cam_periph.o \
	cam_queue.o cam_sim.o cam_xpt.o ata_all.o ata_xpt.o scsi_xpt.o \
	scsi_all.o scsi_cd.o scsi_ch.o ata_da.o scsi_da.o scsi_low.o \
	scsi_low_pisa.o scsi_pass.o scsi_sa.o scsi_ses.o dsfield.o \
	dsinit.o dsmethod.o dsmthdat.o dsobject.o dsopcode.o dsutils.o \
	dswexec.o dswload.o dswscope.o dswstate.o evevent.o evgpe.o \
	evgpeblk.o evmisc.o evregion.o evrgnini.o evsci.o evxface.o \
	evxfevnt.o evxfregn.o exconfig.o exconvrt.o excreate.o exdump.o \
	exfield.o exfldio.o exmisc.o exmutex.o exnames.o exoparg1.o \
	exoparg2.o exoparg3.o exoparg6.o exprep.o exregion.o exresnte.o \
	exresolv.o exresop.o exstore.o exstoren.o exstorob.o exsystem.o \
	exutils.o hwacpi.o hwgpe.o hwregs.o hwsleep.o hwtimer.o \
	hwvalid.o hwxface.o nsaccess.o nsalloc.o nsdump.o nseval.o \
	nsinit.o nsload.o nsnames.o nsobject.o nsparse.o nspredef.o \
	nssearch.o nsutils.o nswalk.o nsxfeval.o nsxfname.o nsxfobj.o \
	psargs.o psloop.o psopcode.o psparse.o psscope.o pstree.o \
	psutils.o pswalk.o psxface.o rsaddr.o rscalc.o rscreate.o \
	rsdump.o rsinfo.o rsio.o rsirq.o rslist.o rsmemory.o rsmisc.o \
	rsutils.o rsxface.o tbfadt.o tbfind.o tbinstal.o tbutils.o \
	tbxface.o tbxfroot.o utalloc.o utcache.o utcopy.o utdebug.o \
	utdelete.o uteval.o utglobal.o utinit.o utlock.o utmath.o \
	utmisc.o utmutex.o utobject.o utresrc.o utstate.o utxface.o \
	rijndael-alg-fst.o rijndael-api-fst.o rijndael-api.o sha1.o \
	sha2.o aac.o aac_cam.o aac_debug.o aac_disk.o aac_pci.o \
	OsdDebug.o OsdHardware.o OsdInterrupt.o OsdMemory.o \
	OsdSchedule.o OsdStream.o OsdSynch.o OsdTable.o acpi.o \
	acpi_acad.o acpi_battery.o acpi_button.o acpi_cmbat.o acpi_cpu.o \
	acpi_ec.o acpi_hpet.o acpi_isab.o acpi_lid.o acpi_package.o \
	acpi_pci.o acpi_pci_link.o acpi_pcib.o acpi_pcib_acpi.o \
	acpi_pcib_pci.o acpi_perf.o acpi_powerres.o acpi_quirk.o \
	acpi_resource.o acpi_smbat.o acpi_thermal.o acpi_throttle.o \
	acpi_timer.o adv_eisa.o adv_pci.o advansys.o advlib.o advmcode.o \
	adw_pci.o adwcam.o adwlib.o adwmcode.o if_ae.o if_age.o agp.o \
	agp_if.o aha.o aha_isa.o ahb.o aic.o aic_pccard.o ahc_eisa.o \
	ahc_isa.o ahc_pci.o ahd_pci.o aic7770.o aic79xx.o aic79xx_osm.o \
	aic79xx_pci.o aic7xxx.o aic7xxx_93cx6.o aic7xxx_osm.o \
	aic7xxx_pci.o if_alc.o if_ale.o amd.o amr.o amr_disk.o amr_pci.o \
	if_an.o if_an_isa.o if_an_pccard.o if_an_pci.o asr.o ata_if.o \
	ata-all.o ata-dma.o ata-lowlevel.o ata-queue.o ata-sata.o \
	ata-card.o ata-isa.o ata-pci.o ata-ahci.o ata-acard.o \
	ata-acerlabs.o ata-adaptec.o ata-amd.o ata-ati.o ata-cenatek.o \
	ata-cypress.o ata-cyrix.o ata-highpoint.o ata-intel.o ata-ite.o \
	ata-jmicron.o ata-marvell.o ata-micron.o ata-national.o \
	ata-netcell.o ata-nvidia.o ata-promise.o ata-serverworks.o \
	ata-siliconimage.o ata-sis.o ata-via.o ata-disk.o ata-raid.o \
	atapi-cd.o atapi-fd.o atapi-tape.o if_ath.o if_ath_pci.o \
	ah_osdep.o ah.o ah_eeprom_v1.o ah_eeprom_v3.o ah_eeprom_v14.o \
	ah_regdomain.o ar5210_attach.o ar5210_beacon.o \
	ar5210_interrupts.o ar5210_keycache.o ar5210_misc.o ar5210_phy.o \
	ar5210_power.o ar5210_recv.o ar5210_reset.o ar5210_xmit.o \
	ar5211_attach.o ar5211_beacon.o ar5211_interrupts.o \
	ar5211_keycache.o ar5211_misc.o ar5211_phy.o ar5211_power.o \
	ar5211_recv.o ar5211_reset.o ar5211_xmit.o ar5212_ani.o \
	ar5212_attach.o ar5212_beacon.o ar5212_eeprom.o ar5212_gpio.o \
	ar5212_interrupts.o ar5212_keycache.o ar5212_misc.o ar5212_phy.o \
	ar5212_power.o ar5212_recv.o ar5212_reset.o ar5212_rfgain.o \
	ar5212_xmit.o ar5416_ani.o ar5416_attach.o ar5416_beacon.o \
	ar5416_cal.o ar5416_cal_iq.o ar5416_cal_adcgain.o \
	ar5416_cal_adcdc.o ar5416_eeprom.o ar5416_gpio.o \
	ar5416_interrupts.o ar5416_keycache.o ar5416_misc.o ar5416_phy.o \
	ar5416_power.o ar5416_recv.o ar5416_reset.o ar5416_xmit.o \
	ar9160_attach.o ar9280_attach.o ar2413.o ar2425.o ar5111.o \
	ar5112.o ar5413.o ar2133.o ar9280.o sample.o if_bce.o if_bfe.o \
	if_bge.o bt.o bt_eisa.o bt_isa.o bt_pci.o cardbus.o \
	cardbus_cis.o cardbus_device.o ciss.o ichss.o if_cs.o \
	if_cs_isa.o if_cs_pccard.o if_dc.o dcphy.o pnphy.o dcons.o \
	dcons_crom.o dcons_os.o if_de.o dpt_eisa.o dpt_pci.o dpt_scsi.o \
	if_ed.o if_ed_novell.o if_ed_rtl80x9.o if_ed_pccard.o \
	if_ed_pci.o eisa_if.o eisaconf.o if_em.o if_igb.o \
	e1000_80003es2lan.o e1000_82540.o e1000_82541.o e1000_82542.o \
	e1000_82543.o e1000_82571.o e1000_82575.o e1000_ich8lan.o \
	e1000_api.o e1000_mac.o e1000_manage.o e1000_nvm.o e1000_phy.o \
	e1000_osdep.o if_et.o if_ep.o if_ep_eisa.o if_ep_isa.o \
	if_ep_pccard.o if_ex.o if_ex_isa.o if_ex_pccard.o exca.o \
	splash.o if_fe.o if_fe_pccard.o firewire.o fwcrom.o fwdev.o \
	fwdma.o fwmem.o fwohci.o fwohci_pci.o if_fwe.o if_fwip.o \
	if_fxp.o hptiop.o ida.o ida_disk.o ida_eisa.o ida_pci.o if_ie.o \
	if_ie_isa.o iir.o iir_ctrl.o iir_pci.o ips.o ips_commands.o \
	ips_disk.o ips_ioctl.o ips_pci.o isp.o isp_freebsd.o \
	isp_library.o isp_pci.o isp_target.o if_ixgb.o ixgb_ee.o \
	ixgb_hw.o if_jme.o kbdmux.o am7990.o am79900.o if_le_pci.o \
	lance.o led.o if_lge.o md.o memdev.o mfi.o mfi_debug.o mfi_pci.o \
	mfi_disk.o acphy.o amphy.o atphy.o axphy.o bmtphy.o brgphy.o \
	ciphy.o e1000phy.o exphy.o gentbi.o icsphy.o inphy.o ip1000phy.o \
	jmphy.o lxtphy.o mii.o mii_physubr.o miibus_if.o mlphy.o \
	nsgphy.o nsphy.o nsphyter.o pnaphy.o qsphy.o rgephy.o rlphy.o \
	ruephy.o smcphy.o tdkphy.o tlphy.o truephy.o ukphy.o \
	ukphy_subr.o xmphy.o mlx.o mlx_disk.o mlx_pci.o mly.o mmcbr_if.o \
	mmcbus_if.o mpt.o mpt_cam.o mpt_debug.o mpt_pci.o mpt_raid.o \
	mpt_user.o if_msk.o ncr53c500.o ncr53c500_pccard.o if_nge.o \
	nsp.o nsp_pccard.o null.o card_if.o pccard.o pccard_cis.o \
	pccard_cis_quirks.o pccard_device.o power_if.o pccbb.o \
	pccbb_isa.o pccbb_pci.o eisa_pci.o fixup_pci.o hostb_pci.o \
	ignore_pci.o isa_pci.o pci.o pci_if.o pci_pci.o pci_user.o \
	pcib_if.o vga_pci.o if_pcn.o if_plip.o lpt.o ppb_1284.o \
	ppb_base.o ppb_msq.o ppbconf.o ppbus_if.o ppi.o ppc.o ppc_acpi.o \
	ppc_isa.o ppc_pci.o pst-iop.o pst-pci.o pst-raid.o rt2560.o \
	rt2661.o if_ral_pci.o harvest.o hash.o probe.o randomdev.o \
	randomdev_soft.o yarrow.o if_re.o if_sf.o if_sis.o if_sk.o \
	if_sn.o if_sn_isa.o if_sn_pccard.o if_ste.o tmc18c30.o \
	tmc18c30_isa.o tmc18c30_pccard.o tmc18c30_pci.o tmc18c30_subr.o \
	if_stge.o sym_hipd.o schistory.o scmouse.o scterm.o scvidctl.o \
	syscons.o sysmouse.o if_ti.o if_tl.o trm.o tw_cl_init.o \
	tw_cl_intr.o tw_cl_io.o tw_cl_misc.o tw_osl_cam.o \
	tw_osl_freebsd.o twe.o twe_freebsd.o if_tx.o if_txp.o \
	uart_bus_acpi.o uart_bus_isa.o uart_bus_pccard.o uart_bus_pci.o \
	uart_core.o uart_dev_ns8250.o uart_if.o uart_subr.o uart_tty.o \
	ehci.o ehci_pci.o ohci.o ohci_pci.o uhci.o uhci_pci.o \
	usb_controller.o umass.o urio.o usb_busdma.o usb_compat_linux.o \
	usb_core.o usb_debug.o usb_dev.o usb_device.o usb_dynamic.o \
	usb_error.o usb_generic.o usb_handle_request.o usb_hid.o \
	usb_hub.o usb_if.o usb_lookup.o usb_mbuf.o usb_msctest.o \
	usb_parse.o usb_process.o usb_request.o usb_transfer.o \
	usb_util.o if_aue.o if_axe.o if_cdce.o if_cue.o if_kue.o \
	if_rue.o if_udav.o usb_ethernet.o if_rum.o if_uath.o if_ural.o \
	if_zyd.o u3g.o uark.o ubsa.o uftdi.o uipaq.o ulpt.o uplcom.o \
	uslcom.o uvisor.o uvscom.o usb_serial.o uhid.o ukbd.o ums.o \
	usb_quirk.o if_vge.o if_vr.o if_vx.o if_vx_eisa.o if_vx_pci.o \
	watchdog.o if_wb.o if_wi.o if_wi_pccard.o if_wi_pci.o if_xe.o \
	if_xe_pccard.o if_xl.o dead_vnops.o devfs_devs.o devfs_rule.o \
	devfs_vfsops.o devfs_vnops.o fifo_vnops.o msdosfs_conv.o \
	msdosfs_denode.o msdosfs_fat.o msdosfs_fileno.o msdosfs_lookup.o \
	msdosfs_vfsops.o msdosfs_vnops.o procfs.o procfs_ctl.o \
	procfs_dbregs.o procfs_fpregs.o procfs_ioctl.o procfs_map.o \
	procfs_mem.o procfs_note.o procfs_regs.o procfs_rlimit.o \
	procfs_status.o procfs_type.o pseudofs.o pseudofs_fileno.o \
	pseudofs_vncache.o pseudofs_vnops.o geom_ctl.o geom_dev.o \
	geom_disk.o geom_dump.o geom_event.o geom_io.o geom_kern.o \
	geom_slice.o geom_subr.o geom_vfs.o g_label.o g_label_ext2fs.o \
	g_label_iso9660.o g_label_msdosfs.o g_label_ntfs.o \
	g_label_reiserfs.o g_label_ufs.o g_label_gpt.o g_part.o \
	g_part_if.o g_part_bsd.o g_part_ebr.o g_part_gpt.o g_part_mbr.o \
	isa_if.o isa_common.o isahint.o orm.o pnp.o pnpparse.o \
	cd9660_bmap.o cd9660_lookup.o cd9660_node.o cd9660_rrip.o \
	cd9660_util.o cd9660_vfsops.o cd9660_vnops.o bus_if.o clock_if.o \
	cpufreq_if.o device_if.o imgact_elf.o imgact_shell.o init_main.o \
	init_sysent.o ksched.o kern_acct.o kern_clock.o kern_condvar.o \
	kern_conf.o kern_cons.o kern_cpu.o kern_cpuset.o kern_context.o \
	kern_descrip.o kern_environment.o kern_event.o kern_exec.o \
	kern_exit.o kern_fail.o kern_fork.o kern_idle.o kern_intr.o \
	kern_jail.o kern_kthread.o kern_ktrace.o kern_linker.o \
	kern_lock.o kern_lockf.o kern_malloc.o kern_mbuf.o kern_mib.o \
	kern_module.o kern_mtxpool.o kern_mutex.o kern_ntptime.o \
	kern_osd.o kern_physio.o kern_pmc.o kern_priv.o kern_proc.o \
	kern_prot.o kern_resource.o kern_rmlock.o kern_rwlock.o \
	kern_sema.o kern_shutdown.o kern_sig.o kern_subr.o kern_switch.o \
	kern_sx.o kern_synch.o kern_syscalls.o kern_sysctl.o kern_tc.o \
	kern_thr.o kern_thread.o kern_time.o kern_timeout.o kern_umtx.o \
	kern_uuid.o kern_xxx.o link_elf.o linker_if.o md5c.o p1003_1b.o \
	posix4_mib.o sched_ule.o serdev_if.o stack_protector.o \
	subr_acl_posix1e.o subr_autoconf.o subr_blist.o subr_bus.o \
	subr_bufring.o subr_clock.o subr_devstat.o subr_disk.o \
	subr_eventhandler.o subr_fattime.o subr_firmware.o subr_hints.o \
	subr_kdb.o subr_kobj.o subr_lock.o subr_log.o subr_module.o \
	subr_msgbuf.o subr_param.o subr_pcpu.o subr_power.o subr_prf.o \
	subr_prof.o subr_rman.o subr_rtc.o subr_sbuf.o subr_scanf.o \
	subr_sglist.o subr_sleepqueue.o subr_smp.o subr_stack.o \
	subr_taskqueue.o subr_trap.o subr_turnstile.o subr_unit.o \
	sys_generic.o sys_pipe.o sys_process.o sys_socket.o sysv_ipc.o \
	sysv_msg.o sysv_sem.o sysv_shm.o tty.o tty_compat.o tty_info.o \
	tty_inq.o tty_outq.o tty_pts.o tty_pty.o tty_tty.o tty_ttydisc.o \
	uipc_accf.o uipc_domain.o uipc_mbuf.o uipc_mbuf2.o uipc_sem.o \
	uipc_shm.o uipc_sockbuf.o uipc_socket.o uipc_syscalls.o \
	uipc_usrreq.o vfs_acl.o vfs_bio.o vfs_cache.o vfs_cluster.o \
	vfs_default.o vfs_export.o vfs_extattr.o vfs_hash.o vfs_init.o \
	vfs_lookup.o vfs_mount.o vfs_subr.o vfs_syscalls.o vfs_vnops.o \
	arc4random.o bcd.o bsearch.o crc32.o fnmatch.o gets.o index.o \
	inet_ntoa.o memcmp.o qsort.o qsort_r.o random.o rindex.o scanc.o \
	skpc.o strcasecmp.o strcat.o strcmp.o strcpy.o strcspn.o \
	strdup.o strlcat.o strlcpy.o strlen.o strncmp.o strncpy.o \
	strsep.o strspn.o strstr.o strtol.o strtoq.o strtoul.o strtouq.o \
	strvalid.o bpf.o bpf_buffer.o bpf_filter.o bpf_zerocopy.o \
	flowtable.o if.o if_clone.o if_dead.o if_ethersubr.o if_faith.o \
	if_fwsubr.o if_gif.o if_loop.o if_llatbl.o if_media.o if_mib.o \
	if_tun.o netisr.o pfil.o radix.o radix_mpath.o raw_cb.o \
	raw_usrreq.o route.o rtsock.o ieee80211.o ieee80211_action.o \
	ieee80211_ageq.o ieee80211_adhoc.o ieee80211_amrr.o \
	ieee80211_crypto.o ieee80211_crypto_ccmp.o \
	ieee80211_crypto_none.o ieee80211_crypto_tkip.o \
	ieee80211_crypto_wep.o ieee80211_dfs.o ieee80211_freebsd.o \
	ieee80211_hostap.o ieee80211_ht.o ieee80211_hwmp.o \
	ieee80211_input.o ieee80211_ioctl.o ieee80211_mesh.o \
	ieee80211_monitor.o ieee80211_node.o ieee80211_output.o \
	ieee80211_phy.o ieee80211_power.o ieee80211_proto.o \
	ieee80211_radiotap.o ieee80211_regdomain.o ieee80211_scan.o \
	ieee80211_scan_sta.o ieee80211_sta.o ieee80211_wds.o if_ether.o \
	igmp.o in.o in_gif.o ip_id.o in_mcast.o in_pcb.o in_proto.o \
	in_rmx.o ip_ecn.o ip_encap.o ip_fastfwd.o ip_icmp.o ip_input.o \
	ip_options.o ip_output.o raw_ip.o sctp_asconf.o sctp_auth.o \
	sctp_bsd_addr.o sctp_cc_functions.o sctp_crc32.o sctp_indata.o \
	sctp_input.o sctp_output.o sctp_pcb.o sctp_peeloff.o \
	sctp_sysctl.o sctp_timer.o sctp_usrreq.o sctputil.o \
	tcp_hostcache.o tcp_input.o tcp_lro.o tcp_output.o tcp_offload.o \
	tcp_reass.o tcp_sack.o tcp_subr.o tcp_syncache.o tcp_timer.o \
	tcp_timewait.o tcp_usrreq.o udp_usrreq.o dest6.o frag6.o icmp6.o \
	in6.o in6_cksum.o in6_gif.o in6_ifattach.o in6_mcast.o in6_pcb.o \
	in6_proto.o in6_rmx.o in6_src.o ip6_forward.o ip6_id.o \
	ip6_input.o ip6_output.o mld6.o nd6.o nd6_nbr.o nd6_rtr.o \
	raw_ip6.o route6.o scope6.o sctp6_usrreq.o udp6_usrreq.o \
	nfs_common.o nfs_bio.o nfs_diskless.o nfs_node.o nfs_krpc.o \
	nfs_subs.o nfs_nfsiod.o nfs_vfsops.o nfs_vnops.o nfs_lock.o \
	nfs_fha.o nfs_serv.o nfs_srvkrpc.o nfs_srvsubs.o nfs_nfssvc.o \
	nlm_advlock.o nlm_prot_clnt.o nlm_prot_impl.o nlm_prot_server.o \
	nlm_prot_svc.o nlm_prot_xdr.o sm_inter_xdr.o if_rl.o auth_none.o \
	auth_unix.o authunix_prot.o clnt_dg.o clnt_rc.o clnt_vc.o \
	getnetconfig.o inet_ntop.o inet_pton.o replay.o rpc_callmsg.o \
	rpc_generic.o rpc_prot.o rpcb_clnt.o rpcb_prot.o svc.o \
	svc_auth.o svc_auth_unix.o svc_dg.o svc_generic.o svc_vc.o \
	audit.o audit_arg.o audit_bsm.o audit_bsm_domain.o \
	audit_bsm_errno.o audit_bsm_fcntl.o audit_bsm_klib.o \
	audit_bsm_socket_type.o audit_bsm_token.o audit_pipe.o \
	audit_syscalls.o audit_trigger.o audit_worker.o mac_audit.o \
	mac_cred.o mac_framework.o mac_inet.o mac_inet6.o mac_label.o \
	mac_net.o mac_pipe.o mac_posix_sem.o mac_posix_shm.o mac_priv.o \
	mac_process.o mac_socket.o mac_syscalls.o mac_system.o \
	mac_sysv_msg.o mac_sysv_sem.o mac_sysv_shm.o mac_vfs.o \
	ffs_alloc.o ffs_balloc.o ffs_inode.o ffs_snapshot.o \
	ffs_softdep.o ffs_subr.o ffs_tables.o ffs_vfsops.o ffs_vnops.o \
	ufs_acl.o ufs_bmap.o ufs_dirhash.o ufs_extattr.o ufs_gjournal.o \
	ufs_inode.o ufs_lookup.o ufs_quota.o ufs_vfsops.o ufs_vnops.o \
	default_pager.o device_pager.o phys_pager.o sg_pager.o \
	swap_pager.o uma_core.o uma_dbg.o vm_contig.o vm_fault.o \
	vm_glue.o vm_init.o vm_kern.o vm_map.o vm_meter.o vm_mmap.o \
	vm_object.o vm_page.o vm_pageout.o vm_pager.o vm_phys.o \
	vm_reserv.o vm_unix.o vm_zeroidle.o vnode_pager.o xdr.o \
	xdr_array.o xdr_mbuf.o xdr_mem.o xdr_reference.o xdr_sizeof.o \
	hptmvraid.o hptrr_lib.o adv_isa.o agp_ali.o agp_amd.o \
	agp_amd64.o agp_ati.o agp_i810.o agp_intel.o agp_nvidia.o \
	agp_sis.o agp_via.o aic_isa.o arcmsr.o atkbd.o atkbd_atkbdc.o \
	atkbdc.o atkbdc_isa.o atkbdc_subr.o psm.o if_ed_isa.o \
	if_ed_wd80x3.o fb.o vga.o fdc.o fdc_acpi.o fdc_isa.o \
	fdc_pccard.o if_fe_isa.o entry.o mv.o gui_lib.o hptproc.o \
	ioctl.o hptrr_os_bsd.o hptrr_osm_bsd.o hptrr_config.o iodev.o \
	kbd.o if_le_isa.o memutil.o if_nfe.o nehemiah.o scterm-teken.o \
	scvgarndr.o scvtb.o teken.o uart_cpu_i386.o acpi_if.o \
	acpi_wmi_if.o OsdEnvironment.o acpi_machdep.o acpi_wakeup.o \
	madt.o est.o hwpstate.o p4tcc.o powernow.o smist.o atomic.o \
	autoconf.o bios.o bioscall.o busdma_machdep.o dump_machdep.o \
	elf_machdep.o exception.o i686_mem.o identcpu.o in_cksum.o \
	initcpu.o intr_machdep.o io.o io_apic.o k6_mem.o legacy.o \
	local_apic.o machdep.o mca.o mem.o minidump_machdep.o mp_clock.o \
	mp_machdep.o mpboot.o mptable.o mptable_pci.o msi.o nexus.o \
	pmap.o ptrace_machdep.o stack_machdep.o support.o swtch.o \
	sys_machdep.o trap.o tsc.o uio_machdep.o vm86.o vm_machdep.o \
	atpic.o clock.o elcr.o elink.o isa.o isa_dma.o nmi.o npx.o \
	pmtimer.o pci_bus.o pci_cfgreg.o pci_pir.o atrtc.o syscons_isa.o \
	vga_isa.o divdi3.o ffsl.o flsl.o memmove.o memset.o moddi3.o \
	qdivrem.o ucmpdi2.o udivdi3.o umoddi3.o 

CFILES=aic7xxx_reg_print.c aic79xx_reg_print.c $S/cam/cam.c \
	$S/cam/cam_periph.c $S/cam/cam_queue.c $S/cam/cam_sim.c \
	$S/cam/cam_xpt.c $S/cam/ata/ata_all.c $S/cam/ata/ata_xpt.c \
	$S/cam/scsi/scsi_xpt.c $S/cam/scsi/scsi_all.c \
	$S/cam/scsi/scsi_cd.c $S/cam/scsi/scsi_ch.c $S/cam/ata/ata_da.c \
	$S/cam/scsi/scsi_da.c $S/cam/scsi/scsi_low.c \
	$S/cam/scsi/scsi_low_pisa.c $S/cam/scsi/scsi_pass.c \
	$S/cam/scsi/scsi_sa.c $S/cam/scsi/scsi_ses.c \
	$S/contrib/dev/acpica/dispatcher/dsfield.c \
	$S/contrib/dev/acpica/dispatcher/dsinit.c \
	$S/contrib/dev/acpica/dispatcher/dsmethod.c \
	$S/contrib/dev/acpica/dispatcher/dsmthdat.c \
	$S/contrib/dev/acpica/dispatcher/dsobject.c \
	$S/contrib/dev/acpica/dispatcher/dsopcode.c \
	$S/contrib/dev/acpica/dispatcher/dsutils.c \
	$S/contrib/dev/acpica/dispatcher/dswexec.c \
	$S/contrib/dev/acpica/dispatcher/dswload.c \
	$S/contrib/dev/acpica/dispatcher/dswscope.c \
	$S/contrib/dev/acpica/dispatcher/dswstate.c \
	$S/contrib/dev/acpica/events/evevent.c \
	$S/contrib/dev/acpica/events/evgpe.c \
	$S/contrib/dev/acpica/events/evgpeblk.c \
	$S/contrib/dev/acpica/events/evmisc.c \
	$S/contrib/dev/acpica/events/evregion.c \
	$S/contrib/dev/acpica/events/evrgnini.c \
	$S/contrib/dev/acpica/events/evsci.c \
	$S/contrib/dev/acpica/events/evxface.c \
	$S/contrib/dev/acpica/events/evxfevnt.c \
	$S/contrib/dev/acpica/events/evxfregn.c \
	$S/contrib/dev/acpica/executer/exconfig.c \
	$S/contrib/dev/acpica/executer/exconvrt.c \
	$S/contrib/dev/acpica/executer/excreate.c \
	$S/contrib/dev/acpica/executer/exdump.c \
	$S/contrib/dev/acpica/executer/exfield.c \
	$S/contrib/dev/acpica/executer/exfldio.c \
	$S/contrib/dev/acpica/executer/exmisc.c \
	$S/contrib/dev/acpica/executer/exmutex.c \
	$S/contrib/dev/acpica/executer/exnames.c \
	$S/contrib/dev/acpica/executer/exoparg1.c \
	$S/contrib/dev/acpica/executer/exoparg2.c \
	$S/contrib/dev/acpica/executer/exoparg3.c \
	$S/contrib/dev/acpica/executer/exoparg6.c \
	$S/contrib/dev/acpica/executer/exprep.c \
	$S/contrib/dev/acpica/executer/exregion.c \
	$S/contrib/dev/acpica/executer/exresnte.c \
	$S/contrib/dev/acpica/executer/exresolv.c \
	$S/contrib/dev/acpica/executer/exresop.c \
	$S/contrib/dev/acpica/executer/exstore.c \
	$S/contrib/dev/acpica/executer/exstoren.c \
	$S/contrib/dev/acpica/executer/exstorob.c \
	$S/contrib/dev/acpica/executer/exsystem.c \
	$S/contrib/dev/acpica/executer/exutils.c \
	$S/contrib/dev/acpica/hardware/hwacpi.c \
	$S/contrib/dev/acpica/hardware/hwgpe.c \
	$S/contrib/dev/acpica/hardware/hwregs.c \
	$S/contrib/dev/acpica/hardware/hwsleep.c \
	$S/contrib/dev/acpica/hardware/hwtimer.c \
	$S/contrib/dev/acpica/hardware/hwvalid.c \
	$S/contrib/dev/acpica/hardware/hwxface.c \
	$S/contrib/dev/acpica/namespace/nsaccess.c \
	$S/contrib/dev/acpica/namespace/nsalloc.c \
	$S/contrib/dev/acpica/namespace/nsdump.c \
	$S/contrib/dev/acpica/namespace/nseval.c \
	$S/contrib/dev/acpica/namespace/nsinit.c \
	$S/contrib/dev/acpica/namespace/nsload.c \
	$S/contrib/dev/acpica/namespace/nsnames.c \
	$S/contrib/dev/acpica/namespace/nsobject.c \
	$S/contrib/dev/acpica/namespace/nsparse.c \
	$S/contrib/dev/acpica/namespace/nspredef.c \
	$S/contrib/dev/acpica/namespace/nssearch.c \
	$S/contrib/dev/acpica/namespace/nsutils.c \
	$S/contrib/dev/acpica/namespace/nswalk.c \
	$S/contrib/dev/acpica/namespace/nsxfeval.c \
	$S/contrib/dev/acpica/namespace/nsxfname.c \
	$S/contrib/dev/acpica/namespace/nsxfobj.c \
	$S/contrib/dev/acpica/parser/psargs.c \
	$S/contrib/dev/acpica/parser/psloop.c \
	$S/contrib/dev/acpica/parser/psopcode.c \
	$S/contrib/dev/acpica/parser/psparse.c \
	$S/contrib/dev/acpica/parser/psscope.c \
	$S/contrib/dev/acpica/parser/pstree.c \
	$S/contrib/dev/acpica/parser/psutils.c \
	$S/contrib/dev/acpica/parser/pswalk.c \
	$S/contrib/dev/acpica/parser/psxface.c \
	$S/contrib/dev/acpica/resources/rsaddr.c \
	$S/contrib/dev/acpica/resources/rscalc.c \
	$S/contrib/dev/acpica/resources/rscreate.c \
	$S/contrib/dev/acpica/resources/rsdump.c \
	$S/contrib/dev/acpica/resources/rsinfo.c \
	$S/contrib/dev/acpica/resources/rsio.c \
	$S/contrib/dev/acpica/resources/rsirq.c \
	$S/contrib/dev/acpica/resources/rslist.c \
	$S/contrib/dev/acpica/resources/rsmemory.c \
	$S/contrib/dev/acpica/resources/rsmisc.c \
	$S/contrib/dev/acpica/resources/rsutils.c \
	$S/contrib/dev/acpica/resources/rsxface.c \
	$S/contrib/dev/acpica/tables/tbfadt.c \
	$S/contrib/dev/acpica/tables/tbfind.c \
	$S/contrib/dev/acpica/tables/tbinstal.c \
	$S/contrib/dev/acpica/tables/tbutils.c \
	$S/contrib/dev/acpica/tables/tbxface.c \
	$S/contrib/dev/acpica/tables/tbxfroot.c \
	$S/contrib/dev/acpica/utilities/utalloc.c \
	$S/contrib/dev/acpica/utilities/utcache.c \
	$S/contrib/dev/acpica/utilities/utcopy.c \
	$S/contrib/dev/acpica/utilities/utdebug.c \
	$S/contrib/dev/acpica/utilities/utdelete.c \
	$S/contrib/dev/acpica/utilities/uteval.c \
	$S/contrib/dev/acpica/utilities/utglobal.c \
	$S/contrib/dev/acpica/utilities/utinit.c \
	$S/contrib/dev/acpica/utilities/utlock.c \
	$S/contrib/dev/acpica/utilities/utmath.c \
	$S/contrib/dev/acpica/utilities/utmisc.c \
	$S/contrib/dev/acpica/utilities/utmutex.c \
	$S/contrib/dev/acpica/utilities/utobject.c \
	$S/contrib/dev/acpica/utilities/utresrc.c \
	$S/contrib/dev/acpica/utilities/utstate.c \
	$S/contrib/dev/acpica/utilities/utxface.c \
	$S/crypto/rijndael/rijndael-alg-fst.c \
	$S/crypto/rijndael/rijndael-api-fst.c \
	$S/crypto/rijndael/rijndael-api.c $S/crypto/sha1.c \
	$S/crypto/sha2/sha2.c $S/dev/aac/aac.c $S/dev/aac/aac_cam.c \
	$S/dev/aac/aac_debug.c $S/dev/aac/aac_disk.c \
	$S/dev/aac/aac_pci.c $S/dev/acpica/Osd/OsdDebug.c \
	$S/dev/acpica/Osd/OsdHardware.c $S/dev/acpica/Osd/OsdInterrupt.c \
	$S/dev/acpica/Osd/OsdMemory.c $S/dev/acpica/Osd/OsdSchedule.c \
	$S/dev/acpica/Osd/OsdStream.c $S/dev/acpica/Osd/OsdSynch.c \
	$S/dev/acpica/Osd/OsdTable.c $S/dev/acpica/acpi.c \
	$S/dev/acpica/acpi_acad.c $S/dev/acpica/acpi_battery.c \
	$S/dev/acpica/acpi_button.c $S/dev/acpica/acpi_cmbat.c \
	$S/dev/acpica/acpi_cpu.c $S/dev/acpica/acpi_ec.c \
	$S/dev/acpica/acpi_hpet.c $S/dev/acpica/acpi_isab.c \
	$S/dev/acpica/acpi_lid.c $S/dev/acpica/acpi_package.c \
	$S/dev/acpica/acpi_pci.c $S/dev/acpica/acpi_pci_link.c \
	$S/dev/acpica/acpi_pcib.c $S/dev/acpica/acpi_pcib_acpi.c \
	$S/dev/acpica/acpi_pcib_pci.c $S/dev/acpica/acpi_perf.c \
	$S/dev/acpica/acpi_powerres.c $S/dev/acpica/acpi_quirk.c \
	$S/dev/acpica/acpi_resource.c $S/dev/acpica/acpi_smbat.c \
	$S/dev/acpica/acpi_thermal.c $S/dev/acpica/acpi_throttle.c \
	$S/dev/acpica/acpi_timer.c $S/dev/advansys/adv_eisa.c \
	$S/dev/advansys/adv_pci.c $S/dev/advansys/advansys.c \
	$S/dev/advansys/advlib.c $S/dev/advansys/advmcode.c \
	$S/dev/advansys/adw_pci.c $S/dev/advansys/adwcam.c \
	$S/dev/advansys/adwlib.c $S/dev/advansys/adwmcode.c \
	$S/dev/ae/if_ae.c $S/dev/age/if_age.c $S/dev/agp/agp.c \
	$S/dev/aha/aha.c $S/dev/aha/aha_isa.c $S/dev/ahb/ahb.c \
	$S/dev/aic/aic.c $S/dev/aic/aic_pccard.c \
	$S/dev/aic7xxx/ahc_eisa.c $S/dev/aic7xxx/ahc_isa.c \
	$S/dev/aic7xxx/ahc_pci.c $S/dev/aic7xxx/ahd_pci.c \
	$S/dev/aic7xxx/aic7770.c $S/dev/aic7xxx/aic79xx.c \
	$S/dev/aic7xxx/aic79xx_osm.c $S/dev/aic7xxx/aic79xx_pci.c \
	$S/dev/aic7xxx/aic7xxx.c $S/dev/aic7xxx/aic7xxx_93cx6.c \
	$S/dev/aic7xxx/aic7xxx_osm.c $S/dev/aic7xxx/aic7xxx_pci.c \
	$S/dev/alc/if_alc.c $S/dev/ale/if_ale.c $S/dev/amd/amd.c \
	$S/dev/amr/amr.c $S/dev/amr/amr_disk.c $S/dev/amr/amr_pci.c \
	$S/dev/an/if_an.c $S/dev/an/if_an_isa.c $S/dev/an/if_an_pccard.c \
	$S/dev/an/if_an_pci.c $S/dev/asr/asr.c $S/dev/ata/ata-all.c \
	$S/dev/ata/ata-dma.c $S/dev/ata/ata-lowlevel.c \
	$S/dev/ata/ata-queue.c $S/dev/ata/ata-sata.c \
	$S/dev/ata/ata-card.c $S/dev/ata/ata-isa.c $S/dev/ata/ata-pci.c \
	$S/dev/ata/chipsets/ata-ahci.c $S/dev/ata/chipsets/ata-acard.c \
	$S/dev/ata/chipsets/ata-acerlabs.c \
	$S/dev/ata/chipsets/ata-adaptec.c $S/dev/ata/chipsets/ata-amd.c \
	$S/dev/ata/chipsets/ata-ati.c $S/dev/ata/chipsets/ata-cenatek.c \
	$S/dev/ata/chipsets/ata-cypress.c \
	$S/dev/ata/chipsets/ata-cyrix.c \
	$S/dev/ata/chipsets/ata-highpoint.c \
	$S/dev/ata/chipsets/ata-intel.c $S/dev/ata/chipsets/ata-ite.c \
	$S/dev/ata/chipsets/ata-jmicron.c \
	$S/dev/ata/chipsets/ata-marvell.c \
	$S/dev/ata/chipsets/ata-micron.c \
	$S/dev/ata/chipsets/ata-national.c \
	$S/dev/ata/chipsets/ata-netcell.c \
	$S/dev/ata/chipsets/ata-nvidia.c \
	$S/dev/ata/chipsets/ata-promise.c \
	$S/dev/ata/chipsets/ata-serverworks.c \
	$S/dev/ata/chipsets/ata-siliconimage.c \
	$S/dev/ata/chipsets/ata-sis.c $S/dev/ata/chipsets/ata-via.c \
	$S/dev/ata/ata-disk.c $S/dev/ata/ata-raid.c \
	$S/dev/ata/atapi-cd.c $S/dev/ata/atapi-fd.c \
	$S/dev/ata/atapi-tape.c $S/dev/ath/if_ath.c \
	$S/dev/ath/if_ath_pci.c $S/dev/ath/ah_osdep.c \
	$S/dev/ath/ath_hal/ah.c $S/dev/ath/ath_hal/ah_eeprom_v1.c \
	$S/dev/ath/ath_hal/ah_eeprom_v3.c \
	$S/dev/ath/ath_hal/ah_eeprom_v14.c \
	$S/dev/ath/ath_hal/ah_regdomain.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_attach.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_beacon.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_interrupts.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_keycache.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_misc.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_phy.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_power.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_recv.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_reset.c \
	$S/dev/ath/ath_hal/ar5210/ar5210_xmit.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_attach.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_beacon.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_interrupts.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_keycache.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_misc.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_phy.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_power.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_recv.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_reset.c \
	$S/dev/ath/ath_hal/ar5211/ar5211_xmit.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_ani.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_attach.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_beacon.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_eeprom.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_gpio.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_interrupts.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_keycache.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_misc.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_phy.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_power.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_recv.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_reset.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_rfgain.c \
	$S/dev/ath/ath_hal/ar5212/ar5212_xmit.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_ani.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_attach.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_beacon.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal_iq.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal_adcgain.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_cal_adcdc.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_eeprom.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_gpio.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_interrupts.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_keycache.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_misc.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_phy.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_power.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_recv.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_reset.c \
	$S/dev/ath/ath_hal/ar5416/ar5416_xmit.c \
	$S/dev/ath/ath_hal/ar5416/ar9160_attach.c \
	$S/dev/ath/ath_hal/ar5416/ar9280_attach.c \
	$S/dev/ath/ath_hal/ar5212/ar2413.c \
	$S/dev/ath/ath_hal/ar5212/ar2425.c \
	$S/dev/ath/ath_hal/ar5212/ar5111.c \
	$S/dev/ath/ath_hal/ar5212/ar5112.c \
	$S/dev/ath/ath_hal/ar5212/ar5413.c \
	$S/dev/ath/ath_hal/ar5416/ar2133.c \
	$S/dev/ath/ath_hal/ar5416/ar9280.c \
	$S/dev/ath/ath_rate/sample/sample.c $S/dev/bce/if_bce.c \
	$S/dev/bfe/if_bfe.c $S/dev/bge/if_bge.c $S/dev/buslogic/bt.c \
	$S/dev/buslogic/bt_eisa.c $S/dev/buslogic/bt_isa.c \
	$S/dev/buslogic/bt_pci.c $S/dev/cardbus/cardbus.c \
	$S/dev/cardbus/cardbus_cis.c $S/dev/cardbus/cardbus_device.c \
	$S/dev/ciss/ciss.c $S/dev/cpufreq/ichss.c $S/dev/cs/if_cs.c \
	$S/dev/cs/if_cs_isa.c $S/dev/cs/if_cs_pccard.c $S/dev/dc/if_dc.c \
	$S/dev/dc/dcphy.c $S/dev/dc/pnphy.c $S/dev/dcons/dcons.c \
	$S/dev/dcons/dcons_crom.c $S/dev/dcons/dcons_os.c \
	$S/dev/de/if_de.c $S/dev/dpt/dpt_eisa.c $S/dev/dpt/dpt_pci.c \
	$S/dev/dpt/dpt_scsi.c $S/dev/ed/if_ed.c $S/dev/ed/if_ed_novell.c \
	$S/dev/ed/if_ed_rtl80x9.c $S/dev/ed/if_ed_pccard.c \
	$S/dev/ed/if_ed_pci.c $S/dev/eisa/eisaconf.c \
	$S/dev/e1000/if_em.c $S/dev/e1000/if_igb.c \
	$S/dev/e1000/e1000_80003es2lan.c $S/dev/e1000/e1000_82540.c \
	$S/dev/e1000/e1000_82541.c $S/dev/e1000/e1000_82542.c \
	$S/dev/e1000/e1000_82543.c $S/dev/e1000/e1000_82571.c \
	$S/dev/e1000/e1000_82575.c $S/dev/e1000/e1000_ich8lan.c \
	$S/dev/e1000/e1000_api.c $S/dev/e1000/e1000_mac.c \
	$S/dev/e1000/e1000_manage.c $S/dev/e1000/e1000_nvm.c \
	$S/dev/e1000/e1000_phy.c $S/dev/e1000/e1000_osdep.c \
	$S/dev/et/if_et.c $S/dev/ep/if_ep.c $S/dev/ep/if_ep_eisa.c \
	$S/dev/ep/if_ep_isa.c $S/dev/ep/if_ep_pccard.c $S/dev/ex/if_ex.c \
	$S/dev/ex/if_ex_isa.c $S/dev/ex/if_ex_pccard.c \
	$S/dev/exca/exca.c $S/dev/fb/splash.c $S/dev/fe/if_fe.c \
	$S/dev/fe/if_fe_pccard.c $S/dev/firewire/firewire.c \
	$S/dev/firewire/fwcrom.c $S/dev/firewire/fwdev.c \
	$S/dev/firewire/fwdma.c $S/dev/firewire/fwmem.c \
	$S/dev/firewire/fwohci.c $S/dev/firewire/fwohci_pci.c \
	$S/dev/firewire/if_fwe.c $S/dev/firewire/if_fwip.c \
	$S/dev/fxp/if_fxp.c $S/dev/hptiop/hptiop.c $S/dev/ida/ida.c \
	$S/dev/ida/ida_disk.c $S/dev/ida/ida_eisa.c $S/dev/ida/ida_pci.c \
	$S/dev/ie/if_ie.c $S/dev/ie/if_ie_isa.c $S/dev/iir/iir.c \
	$S/dev/iir/iir_ctrl.c $S/dev/iir/iir_pci.c $S/dev/ips/ips.c \
	$S/dev/ips/ips_commands.c $S/dev/ips/ips_disk.c \
	$S/dev/ips/ips_ioctl.c $S/dev/ips/ips_pci.c $S/dev/isp/isp.c \
	$S/dev/isp/isp_freebsd.c $S/dev/isp/isp_library.c \
	$S/dev/isp/isp_pci.c $S/dev/isp/isp_target.c \
	$S/dev/ixgb/if_ixgb.c $S/dev/ixgb/ixgb_ee.c \
	$S/dev/ixgb/ixgb_hw.c $S/dev/jme/if_jme.c $S/dev/kbdmux/kbdmux.c \
	$S/dev/le/am7990.c $S/dev/le/am79900.c $S/dev/le/if_le_pci.c \
	$S/dev/le/lance.c $S/dev/led/led.c $S/dev/lge/if_lge.c \
	$S/dev/md/md.c $S/dev/mem/memdev.c $S/dev/mfi/mfi.c \
	$S/dev/mfi/mfi_debug.c $S/dev/mfi/mfi_pci.c \
	$S/dev/mfi/mfi_disk.c $S/dev/mii/acphy.c $S/dev/mii/amphy.c \
	$S/dev/mii/atphy.c $S/dev/mii/axphy.c $S/dev/mii/bmtphy.c \
	$S/dev/mii/brgphy.c $S/dev/mii/ciphy.c $S/dev/mii/e1000phy.c \
	$S/dev/mii/exphy.c $S/dev/mii/gentbi.c $S/dev/mii/icsphy.c \
	$S/dev/mii/inphy.c $S/dev/mii/ip1000phy.c $S/dev/mii/jmphy.c \
	$S/dev/mii/lxtphy.c $S/dev/mii/mii.c $S/dev/mii/mii_physubr.c \
	$S/dev/mii/mlphy.c $S/dev/mii/nsgphy.c $S/dev/mii/nsphy.c \
	$S/dev/mii/nsphyter.c $S/dev/mii/pnaphy.c $S/dev/mii/qsphy.c \
	$S/dev/mii/rgephy.c $S/dev/mii/rlphy.c $S/dev/mii/ruephy.c \
	$S/dev/mii/smcphy.c $S/dev/mii/tdkphy.c $S/dev/mii/tlphy.c \
	$S/dev/mii/truephy.c $S/dev/mii/ukphy.c $S/dev/mii/ukphy_subr.c \
	$S/dev/mii/xmphy.c $S/dev/mlx/mlx.c $S/dev/mlx/mlx_disk.c \
	$S/dev/mlx/mlx_pci.c $S/dev/mly/mly.c $S/dev/mpt/mpt.c \
	$S/dev/mpt/mpt_cam.c $S/dev/mpt/mpt_debug.c $S/dev/mpt/mpt_pci.c \
	$S/dev/mpt/mpt_raid.c $S/dev/mpt/mpt_user.c $S/dev/msk/if_msk.c \
	$S/dev/ncv/ncr53c500.c $S/dev/ncv/ncr53c500_pccard.c \
	$S/dev/nge/if_nge.c $S/dev/nsp/nsp.c $S/dev/nsp/nsp_pccard.c \
	$S/dev/null/null.c $S/dev/pccard/pccard.c \
	$S/dev/pccard/pccard_cis.c $S/dev/pccard/pccard_cis_quirks.c \
	$S/dev/pccard/pccard_device.c $S/dev/pccbb/pccbb.c \
	$S/dev/pccbb/pccbb_isa.c $S/dev/pccbb/pccbb_pci.c \
	$S/dev/pci/eisa_pci.c $S/dev/pci/fixup_pci.c \
	$S/dev/pci/hostb_pci.c $S/dev/pci/ignore_pci.c \
	$S/dev/pci/isa_pci.c $S/dev/pci/pci.c $S/dev/pci/pci_pci.c \
	$S/dev/pci/pci_user.c $S/dev/pci/vga_pci.c $S/dev/pcn/if_pcn.c \
	$S/dev/ppbus/if_plip.c $S/dev/ppbus/lpt.c \
	$S/dev/ppbus/ppb_1284.c $S/dev/ppbus/ppb_base.c \
	$S/dev/ppbus/ppb_msq.c $S/dev/ppbus/ppbconf.c $S/dev/ppbus/ppi.c \
	$S/dev/ppc/ppc.c $S/dev/ppc/ppc_acpi.c $S/dev/ppc/ppc_isa.c \
	$S/dev/ppc/ppc_pci.c $S/dev/pst/pst-iop.c $S/dev/pst/pst-pci.c \
	$S/dev/pst/pst-raid.c $S/dev/ral/rt2560.c $S/dev/ral/rt2661.c \
	$S/dev/ral/if_ral_pci.c $S/dev/random/harvest.c \
	$S/dev/random/hash.c $S/dev/random/probe.c \
	$S/dev/random/randomdev.c $S/dev/random/randomdev_soft.c \
	$S/dev/random/yarrow.c $S/dev/re/if_re.c $S/dev/sf/if_sf.c \
	$S/dev/sis/if_sis.c $S/dev/sk/if_sk.c $S/dev/sn/if_sn.c \
	$S/dev/sn/if_sn_isa.c $S/dev/sn/if_sn_pccard.c \
	$S/dev/ste/if_ste.c $S/dev/stg/tmc18c30.c \
	$S/dev/stg/tmc18c30_isa.c $S/dev/stg/tmc18c30_pccard.c \
	$S/dev/stg/tmc18c30_pci.c $S/dev/stg/tmc18c30_subr.c \
	$S/dev/stge/if_stge.c $S/dev/sym/sym_hipd.c \
	$S/dev/syscons/schistory.c $S/dev/syscons/scmouse.c \
	$S/dev/syscons/scterm.c $S/dev/syscons/scvidctl.c \
	$S/dev/syscons/syscons.c $S/dev/syscons/sysmouse.c \
	$S/dev/ti/if_ti.c $S/dev/tl/if_tl.c $S/dev/trm/trm.c \
	$S/dev/twa/tw_cl_init.c $S/dev/twa/tw_cl_intr.c \
	$S/dev/twa/tw_cl_io.c $S/dev/twa/tw_cl_misc.c \
	$S/dev/twa/tw_osl_cam.c $S/dev/twa/tw_osl_freebsd.c \
	$S/dev/twe/twe.c $S/dev/twe/twe_freebsd.c $S/dev/tx/if_tx.c \
	$S/dev/txp/if_txp.c $S/dev/uart/uart_bus_acpi.c \
	$S/dev/uart/uart_bus_isa.c $S/dev/uart/uart_bus_pccard.c \
	$S/dev/uart/uart_bus_pci.c $S/dev/uart/uart_core.c \
	$S/dev/uart/uart_dev_ns8250.c $S/dev/uart/uart_subr.c \
	$S/dev/uart/uart_tty.c $S/dev/usb/controller/ehci.c \
	$S/dev/usb/controller/ehci_pci.c $S/dev/usb/controller/ohci.c \
	$S/dev/usb/controller/ohci_pci.c $S/dev/usb/controller/uhci.c \
	$S/dev/usb/controller/uhci_pci.c \
	$S/dev/usb/controller/usb_controller.c \
	$S/dev/usb/storage/umass.c $S/dev/usb/storage/urio.c \
	$S/dev/usb/usb_busdma.c $S/dev/usb/usb_compat_linux.c \
	$S/dev/usb/usb_core.c $S/dev/usb/usb_debug.c \
	$S/dev/usb/usb_dev.c $S/dev/usb/usb_device.c \
	$S/dev/usb/usb_dynamic.c $S/dev/usb/usb_error.c \
	$S/dev/usb/usb_generic.c $S/dev/usb/usb_handle_request.c \
	$S/dev/usb/usb_hid.c $S/dev/usb/usb_hub.c \
	$S/dev/usb/usb_lookup.c $S/dev/usb/usb_mbuf.c \
	$S/dev/usb/usb_msctest.c $S/dev/usb/usb_parse.c \
	$S/dev/usb/usb_process.c $S/dev/usb/usb_request.c \
	$S/dev/usb/usb_transfer.c $S/dev/usb/usb_util.c \
	$S/dev/usb/net/if_aue.c $S/dev/usb/net/if_axe.c \
	$S/dev/usb/net/if_cdce.c $S/dev/usb/net/if_cue.c \
	$S/dev/usb/net/if_kue.c $S/dev/usb/net/if_rue.c \
	$S/dev/usb/net/if_udav.c $S/dev/usb/net/usb_ethernet.c \
	$S/dev/usb/wlan/if_rum.c $S/dev/usb/wlan/if_uath.c \
	$S/dev/usb/wlan/if_ural.c $S/dev/usb/wlan/if_zyd.c \
	$S/dev/usb/serial/u3g.c $S/dev/usb/serial/uark.c \
	$S/dev/usb/serial/ubsa.c $S/dev/usb/serial/uftdi.c \
	$S/dev/usb/serial/uipaq.c $S/dev/usb/serial/ulpt.c \
	$S/dev/usb/serial/uplcom.c $S/dev/usb/serial/uslcom.c \
	$S/dev/usb/serial/uvisor.c $S/dev/usb/serial/uvscom.c \
	$S/dev/usb/serial/usb_serial.c $S/dev/usb/input/uhid.c \
	$S/dev/usb/input/ukbd.c $S/dev/usb/input/ums.c \
	$S/dev/usb/quirk/usb_quirk.c $S/dev/vge/if_vge.c \
	$S/dev/vr/if_vr.c $S/dev/vx/if_vx.c $S/dev/vx/if_vx_eisa.c \
	$S/dev/vx/if_vx_pci.c $S/dev/watchdog/watchdog.c \
	$S/dev/wb/if_wb.c $S/dev/wi/if_wi.c $S/dev/wi/if_wi_pccard.c \
	$S/dev/wi/if_wi_pci.c $S/dev/xe/if_xe.c $S/dev/xe/if_xe_pccard.c \
	$S/dev/xl/if_xl.c $S/fs/deadfs/dead_vnops.c \
	$S/fs/devfs/devfs_devs.c $S/fs/devfs/devfs_rule.c \
	$S/fs/devfs/devfs_vfsops.c $S/fs/devfs/devfs_vnops.c \
	$S/fs/fifofs/fifo_vnops.c $S/fs/msdosfs/msdosfs_conv.c \
	$S/fs/msdosfs/msdosfs_denode.c $S/fs/msdosfs/msdosfs_fat.c \
	$S/fs/msdosfs/msdosfs_fileno.c $S/fs/msdosfs/msdosfs_lookup.c \
	$S/fs/msdosfs/msdosfs_vfsops.c $S/fs/msdosfs/msdosfs_vnops.c \
	$S/fs/procfs/procfs.c $S/fs/procfs/procfs_ctl.c \
	$S/fs/procfs/procfs_dbregs.c $S/fs/procfs/procfs_fpregs.c \
	$S/fs/procfs/procfs_ioctl.c $S/fs/procfs/procfs_map.c \
	$S/fs/procfs/procfs_mem.c $S/fs/procfs/procfs_note.c \
	$S/fs/procfs/procfs_regs.c $S/fs/procfs/procfs_rlimit.c \
	$S/fs/procfs/procfs_status.c $S/fs/procfs/procfs_type.c \
	$S/fs/pseudofs/pseudofs.c $S/fs/pseudofs/pseudofs_fileno.c \
	$S/fs/pseudofs/pseudofs_vncache.c \
	$S/fs/pseudofs/pseudofs_vnops.c $S/geom/geom_ctl.c \
	$S/geom/geom_dev.c $S/geom/geom_disk.c $S/geom/geom_dump.c \
	$S/geom/geom_event.c $S/geom/geom_io.c $S/geom/geom_kern.c \
	$S/geom/geom_slice.c $S/geom/geom_subr.c $S/geom/geom_vfs.c \
	$S/geom/label/g_label.c $S/geom/label/g_label_ext2fs.c \
	$S/geom/label/g_label_iso9660.c $S/geom/label/g_label_msdosfs.c \
	$S/geom/label/g_label_ntfs.c $S/geom/label/g_label_reiserfs.c \
	$S/geom/label/g_label_ufs.c $S/geom/label/g_label_gpt.c \
	$S/geom/part/g_part.c $S/geom/part/g_part_bsd.c \
	$S/geom/part/g_part_ebr.c $S/geom/part/g_part_gpt.c \
	$S/geom/part/g_part_mbr.c $S/isa/isa_common.c $S/isa/isahint.c \
	$S/isa/orm.c $S/isa/pnp.c $S/isa/pnpparse.c \
	$S/fs/cd9660/cd9660_bmap.c $S/fs/cd9660/cd9660_lookup.c \
	$S/fs/cd9660/cd9660_node.c $S/fs/cd9660/cd9660_rrip.c \
	$S/fs/cd9660/cd9660_util.c $S/fs/cd9660/cd9660_vfsops.c \
	$S/fs/cd9660/cd9660_vnops.c $S/kern/imgact_elf.c \
	$S/kern/imgact_shell.c $S/kern/init_main.c $S/kern/init_sysent.c \
	$S/kern/ksched.c $S/kern/kern_acct.c $S/kern/kern_clock.c \
	$S/kern/kern_condvar.c $S/kern/kern_conf.c $S/kern/kern_cons.c \
	$S/kern/kern_cpu.c $S/kern/kern_cpuset.c $S/kern/kern_context.c \
	$S/kern/kern_descrip.c $S/kern/kern_environment.c \
	$S/kern/kern_event.c $S/kern/kern_exec.c $S/kern/kern_exit.c \
	$S/kern/kern_fail.c $S/kern/kern_fork.c $S/kern/kern_idle.c \
	$S/kern/kern_intr.c $S/kern/kern_jail.c $S/kern/kern_kthread.c \
	$S/kern/kern_ktrace.c $S/kern/kern_linker.c $S/kern/kern_lock.c \
	$S/kern/kern_lockf.c $S/kern/kern_malloc.c $S/kern/kern_mbuf.c \
	$S/kern/kern_mib.c $S/kern/kern_module.c $S/kern/kern_mtxpool.c \
	$S/kern/kern_mutex.c $S/kern/kern_ntptime.c $S/kern/kern_osd.c \
	$S/kern/kern_physio.c $S/kern/kern_pmc.c $S/kern/kern_priv.c \
	$S/kern/kern_proc.c $S/kern/kern_prot.c $S/kern/kern_resource.c \
	$S/kern/kern_rmlock.c $S/kern/kern_rwlock.c $S/kern/kern_sema.c \
	$S/kern/kern_shutdown.c $S/kern/kern_sig.c $S/kern/kern_subr.c \
	$S/kern/kern_switch.c $S/kern/kern_sx.c $S/kern/kern_synch.c \
	$S/kern/kern_syscalls.c $S/kern/kern_sysctl.c $S/kern/kern_tc.c \
	$S/kern/kern_thr.c $S/kern/kern_thread.c $S/kern/kern_time.c \
	$S/kern/kern_timeout.c $S/kern/kern_umtx.c $S/kern/kern_uuid.c \
	$S/kern/kern_xxx.c $S/kern/link_elf.c $S/kern/md5c.c \
	$S/kern/p1003_1b.c $S/kern/posix4_mib.c $S/kern/sched_ule.c \
	$S/kern/stack_protector.c $S/kern/subr_acl_posix1e.c \
	$S/kern/subr_autoconf.c $S/kern/subr_blist.c $S/kern/subr_bus.c \
	$S/kern/subr_bufring.c $S/kern/subr_clock.c \
	$S/kern/subr_devstat.c $S/kern/subr_disk.c \
	$S/kern/subr_eventhandler.c $S/kern/subr_fattime.c \
	$S/kern/subr_firmware.c $S/kern/subr_hints.c $S/kern/subr_kdb.c \
	$S/kern/subr_kobj.c $S/kern/subr_lock.c $S/kern/subr_log.c \
	$S/kern/subr_module.c $S/kern/subr_msgbuf.c $S/kern/subr_param.c \
	$S/kern/subr_pcpu.c $S/kern/subr_power.c $S/kern/subr_prf.c \
	$S/kern/subr_prof.c $S/kern/subr_rman.c $S/kern/subr_rtc.c \
	$S/kern/subr_sbuf.c $S/kern/subr_scanf.c $S/kern/subr_sglist.c \
	$S/kern/subr_sleepqueue.c $S/kern/subr_smp.c \
	$S/kern/subr_stack.c $S/kern/subr_taskqueue.c \
	$S/kern/subr_trap.c $S/kern/subr_turnstile.c $S/kern/subr_unit.c \
	$S/kern/sys_generic.c $S/kern/sys_pipe.c $S/kern/sys_process.c \
	$S/kern/sys_socket.c $S/kern/sysv_ipc.c $S/kern/sysv_msg.c \
	$S/kern/sysv_sem.c $S/kern/sysv_shm.c $S/kern/tty.c \
	$S/kern/tty_compat.c $S/kern/tty_info.c $S/kern/tty_inq.c \
	$S/kern/tty_outq.c $S/kern/tty_pts.c $S/kern/tty_pty.c \
	$S/kern/tty_tty.c $S/kern/tty_ttydisc.c $S/kern/uipc_accf.c \
	$S/kern/uipc_domain.c $S/kern/uipc_mbuf.c $S/kern/uipc_mbuf2.c \
	$S/kern/uipc_sem.c $S/kern/uipc_shm.c $S/kern/uipc_sockbuf.c \
	$S/kern/uipc_socket.c $S/kern/uipc_syscalls.c \
	$S/kern/uipc_usrreq.c $S/kern/vfs_acl.c $S/kern/vfs_bio.c \
	$S/kern/vfs_cache.c $S/kern/vfs_cluster.c $S/kern/vfs_default.c \
	$S/kern/vfs_export.c $S/kern/vfs_extattr.c $S/kern/vfs_hash.c \
	$S/kern/vfs_init.c $S/kern/vfs_lookup.c $S/kern/vfs_mount.c \
	$S/kern/vfs_subr.c $S/kern/vfs_syscalls.c $S/kern/vfs_vnops.c \
	$S/libkern/arc4random.c $S/libkern/bcd.c $S/libkern/bsearch.c \
	$S/libkern/crc32.c $S/libkern/fnmatch.c $S/libkern/gets.c \
	$S/libkern/index.c $S/libkern/inet_ntoa.c $S/libkern/memcmp.c \
	$S/libkern/qsort.c $S/libkern/qsort_r.c $S/libkern/random.c \
	$S/libkern/rindex.c $S/libkern/scanc.c $S/libkern/skpc.c \
	$S/libkern/strcasecmp.c $S/libkern/strcat.c $S/libkern/strcmp.c \
	$S/libkern/strcpy.c $S/libkern/strcspn.c $S/libkern/strdup.c \
	$S/libkern/strlcat.c $S/libkern/strlcpy.c $S/libkern/strlen.c \
	$S/libkern/strncmp.c $S/libkern/strncpy.c $S/libkern/strsep.c \
	$S/libkern/strspn.c $S/libkern/strstr.c $S/libkern/strtol.c \
	$S/libkern/strtoq.c $S/libkern/strtoul.c $S/libkern/strtouq.c \
	$S/libkern/strvalid.c $S/net/bpf.c $S/net/bpf_buffer.c \
	$S/net/bpf_filter.c $S/net/bpf_zerocopy.c $S/net/flowtable.c \
	$S/net/if.c $S/net/if_clone.c $S/net/if_dead.c \
	$S/net/if_ethersubr.c $S/net/if_faith.c $S/net/if_fwsubr.c \
	$S/net/if_gif.c $S/net/if_loop.c $S/net/if_llatbl.c \
	$S/net/if_media.c $S/net/if_mib.c $S/net/if_tun.c \
	$S/net/netisr.c $S/net/pfil.c $S/net/radix.c \
	$S/net/radix_mpath.c $S/net/raw_cb.c $S/net/raw_usrreq.c \
	$S/net/route.c $S/net/rtsock.c $S/net80211/ieee80211.c \
	$S/net80211/ieee80211_action.c $S/net80211/ieee80211_ageq.c \
	$S/net80211/ieee80211_adhoc.c $S/net80211/ieee80211_amrr.c \
	$S/net80211/ieee80211_crypto.c \
	$S/net80211/ieee80211_crypto_ccmp.c \
	$S/net80211/ieee80211_crypto_none.c \
	$S/net80211/ieee80211_crypto_tkip.c \
	$S/net80211/ieee80211_crypto_wep.c $S/net80211/ieee80211_dfs.c \
	$S/net80211/ieee80211_freebsd.c $S/net80211/ieee80211_hostap.c \
	$S/net80211/ieee80211_ht.c $S/net80211/ieee80211_hwmp.c \
	$S/net80211/ieee80211_input.c $S/net80211/ieee80211_ioctl.c \
	$S/net80211/ieee80211_mesh.c $S/net80211/ieee80211_monitor.c \
	$S/net80211/ieee80211_node.c $S/net80211/ieee80211_output.c \
	$S/net80211/ieee80211_phy.c $S/net80211/ieee80211_power.c \
	$S/net80211/ieee80211_proto.c $S/net80211/ieee80211_radiotap.c \
	$S/net80211/ieee80211_regdomain.c $S/net80211/ieee80211_scan.c \
	$S/net80211/ieee80211_scan_sta.c $S/net80211/ieee80211_sta.c \
	$S/net80211/ieee80211_wds.c $S/netinet/if_ether.c \
	$S/netinet/igmp.c $S/netinet/in.c $S/netinet/in_gif.c \
	$S/netinet/ip_id.c $S/netinet/in_mcast.c $S/netinet/in_pcb.c \
	$S/netinet/in_proto.c $S/netinet/in_rmx.c $S/netinet/ip_ecn.c \
	$S/netinet/ip_encap.c $S/netinet/ip_fastfwd.c \
	$S/netinet/ip_icmp.c $S/netinet/ip_input.c \
	$S/netinet/ip_options.c $S/netinet/ip_output.c \
	$S/netinet/raw_ip.c $S/netinet/sctp_asconf.c \
	$S/netinet/sctp_auth.c $S/netinet/sctp_bsd_addr.c \
	$S/netinet/sctp_cc_functions.c $S/netinet/sctp_crc32.c \
	$S/netinet/sctp_indata.c $S/netinet/sctp_input.c \
	$S/netinet/sctp_output.c $S/netinet/sctp_pcb.c \
	$S/netinet/sctp_peeloff.c $S/netinet/sctp_sysctl.c \
	$S/netinet/sctp_timer.c $S/netinet/sctp_usrreq.c \
	$S/netinet/sctputil.c $S/netinet/tcp_hostcache.c \
	$S/netinet/tcp_input.c $S/netinet/tcp_lro.c \
	$S/netinet/tcp_output.c $S/netinet/tcp_offload.c \
	$S/netinet/tcp_reass.c $S/netinet/tcp_sack.c \
	$S/netinet/tcp_subr.c $S/netinet/tcp_syncache.c \
	$S/netinet/tcp_timer.c $S/netinet/tcp_timewait.c \
	$S/netinet/tcp_usrreq.c $S/netinet/udp_usrreq.c \
	$S/netinet6/dest6.c $S/netinet6/frag6.c $S/netinet6/icmp6.c \
	$S/netinet6/in6.c $S/netinet6/in6_cksum.c $S/netinet6/in6_gif.c \
	$S/netinet6/in6_ifattach.c $S/netinet6/in6_mcast.c \
	$S/netinet6/in6_pcb.c $S/netinet6/in6_proto.c \
	$S/netinet6/in6_rmx.c $S/netinet6/in6_src.c \
	$S/netinet6/ip6_forward.c $S/netinet6/ip6_id.c \
	$S/netinet6/ip6_input.c $S/netinet6/ip6_output.c \
	$S/netinet6/mld6.c $S/netinet6/nd6.c $S/netinet6/nd6_nbr.c \
	$S/netinet6/nd6_rtr.c $S/netinet6/raw_ip6.c $S/netinet6/route6.c \
	$S/netinet6/scope6.c $S/netinet6/sctp6_usrreq.c \
	$S/netinet6/udp6_usrreq.c $S/nfs/nfs_common.c \
	$S/nfsclient/nfs_bio.c $S/nfsclient/nfs_diskless.c \
	$S/nfsclient/nfs_node.c $S/nfsclient/nfs_krpc.c \
	$S/nfsclient/nfs_subs.c $S/nfsclient/nfs_nfsiod.c \
	$S/nfsclient/nfs_vfsops.c $S/nfsclient/nfs_vnops.c \
	$S/nfsclient/nfs_lock.c $S/nfsserver/nfs_fha.c \
	$S/nfsserver/nfs_serv.c $S/nfsserver/nfs_srvkrpc.c \
	$S/nfsserver/nfs_srvsubs.c $S/nfs/nfs_nfssvc.c \
	$S/nlm/nlm_advlock.c $S/nlm/nlm_prot_clnt.c \
	$S/nlm/nlm_prot_impl.c $S/nlm/nlm_prot_server.c \
	$S/nlm/nlm_prot_svc.c $S/nlm/nlm_prot_xdr.c \
	$S/nlm/sm_inter_xdr.c $S/pci/if_rl.c $S/rpc/auth_none.c \
	$S/rpc/auth_unix.c $S/rpc/authunix_prot.c $S/rpc/clnt_dg.c \
	$S/rpc/clnt_rc.c $S/rpc/clnt_vc.c $S/rpc/getnetconfig.c \
	$S/rpc/inet_ntop.c $S/rpc/inet_pton.c $S/rpc/replay.c \
	$S/rpc/rpc_callmsg.c $S/rpc/rpc_generic.c $S/rpc/rpc_prot.c \
	$S/rpc/rpcb_clnt.c $S/rpc/rpcb_prot.c $S/rpc/svc.c \
	$S/rpc/svc_auth.c $S/rpc/svc_auth_unix.c $S/rpc/svc_dg.c \
	$S/rpc/svc_generic.c $S/rpc/svc_vc.c $S/security/audit/audit.c \
	$S/security/audit/audit_arg.c $S/security/audit/audit_bsm.c \
	$S/security/audit/audit_bsm_domain.c \
	$S/security/audit/audit_bsm_errno.c \
	$S/security/audit/audit_bsm_fcntl.c \
	$S/security/audit/audit_bsm_klib.c \
	$S/security/audit/audit_bsm_socket_type.c \
	$S/security/audit/audit_bsm_token.c \
	$S/security/audit/audit_pipe.c \
	$S/security/audit/audit_syscalls.c \
	$S/security/audit/audit_trigger.c \
	$S/security/audit/audit_worker.c $S/security/mac/mac_audit.c \
	$S/security/mac/mac_cred.c $S/security/mac/mac_framework.c \
	$S/security/mac/mac_inet.c $S/security/mac/mac_inet6.c \
	$S/security/mac/mac_label.c $S/security/mac/mac_net.c \
	$S/security/mac/mac_pipe.c $S/security/mac/mac_posix_sem.c \
	$S/security/mac/mac_posix_shm.c $S/security/mac/mac_priv.c \
	$S/security/mac/mac_process.c $S/security/mac/mac_socket.c \
	$S/security/mac/mac_syscalls.c $S/security/mac/mac_system.c \
	$S/security/mac/mac_sysv_msg.c $S/security/mac/mac_sysv_sem.c \
	$S/security/mac/mac_sysv_shm.c $S/security/mac/mac_vfs.c \
	$S/ufs/ffs/ffs_alloc.c $S/ufs/ffs/ffs_balloc.c \
	$S/ufs/ffs/ffs_inode.c $S/ufs/ffs/ffs_snapshot.c \
	$S/ufs/ffs/ffs_softdep.c $S/ufs/ffs/ffs_subr.c \
	$S/ufs/ffs/ffs_tables.c $S/ufs/ffs/ffs_vfsops.c \
	$S/ufs/ffs/ffs_vnops.c $S/ufs/ufs/ufs_acl.c \
	$S/ufs/ufs/ufs_bmap.c $S/ufs/ufs/ufs_dirhash.c \
	$S/ufs/ufs/ufs_extattr.c $S/ufs/ufs/ufs_gjournal.c \
	$S/ufs/ufs/ufs_inode.c $S/ufs/ufs/ufs_lookup.c \
	$S/ufs/ufs/ufs_quota.c $S/ufs/ufs/ufs_vfsops.c \
	$S/ufs/ufs/ufs_vnops.c $S/vm/default_pager.c \
	$S/vm/device_pager.c $S/vm/phys_pager.c $S/vm/sg_pager.c \
	$S/vm/swap_pager.c $S/vm/uma_core.c $S/vm/uma_dbg.c \
	$S/vm/vm_contig.c $S/vm/vm_fault.c $S/vm/vm_glue.c \
	$S/vm/vm_init.c $S/vm/vm_kern.c $S/vm/vm_map.c $S/vm/vm_meter.c \
	$S/vm/vm_mmap.c $S/vm/vm_object.c $S/vm/vm_page.c \
	$S/vm/vm_pageout.c $S/vm/vm_pager.c $S/vm/vm_phys.c \
	$S/vm/vm_reserv.c $S/vm/vm_unix.c $S/vm/vm_zeroidle.c \
	$S/vm/vnode_pager.c $S/xdr/xdr.c $S/xdr/xdr_array.c \
	$S/xdr/xdr_mbuf.c $S/xdr/xdr_mem.c $S/xdr/xdr_reference.c \
	$S/xdr/xdr_sizeof.c $S/dev/advansys/adv_isa.c \
	$S/dev/agp/agp_ali.c $S/dev/agp/agp_amd.c $S/dev/agp/agp_amd64.c \
	$S/dev/agp/agp_ati.c $S/dev/agp/agp_i810.c \
	$S/dev/agp/agp_intel.c $S/dev/agp/agp_nvidia.c \
	$S/dev/agp/agp_sis.c $S/dev/agp/agp_via.c $S/dev/aic/aic_isa.c \
	$S/dev/arcmsr/arcmsr.c $S/dev/atkbdc/atkbd.c \
	$S/dev/atkbdc/atkbd_atkbdc.c $S/dev/atkbdc/atkbdc.c \
	$S/dev/atkbdc/atkbdc_isa.c $S/dev/atkbdc/atkbdc_subr.c \
	$S/dev/atkbdc/psm.c $S/dev/ed/if_ed_isa.c \
	$S/dev/ed/if_ed_wd80x3.c $S/dev/fb/fb.c $S/dev/fb/vga.c \
	$S/dev/fdc/fdc.c $S/dev/fdc/fdc_acpi.c $S/dev/fdc/fdc_isa.c \
	$S/dev/fdc/fdc_pccard.c $S/dev/fe/if_fe_isa.c \
	$S/dev/hptmv/entry.c $S/dev/hptmv/mv.c $S/dev/hptmv/gui_lib.c \
	$S/dev/hptmv/hptproc.c $S/dev/hptmv/ioctl.c \
	$S/dev/hptrr/hptrr_os_bsd.c $S/dev/hptrr/hptrr_osm_bsd.c \
	$S/dev/hptrr/hptrr_config.c $S/dev/io/iodev.c $S/dev/kbd/kbd.c \
	$S/dev/le/if_le_isa.c $S/dev/mem/memutil.c $S/dev/nfe/if_nfe.c \
	$S/dev/random/nehemiah.c $S/dev/syscons/scterm-teken.c \
	$S/dev/syscons/scvgarndr.c $S/dev/syscons/scvtb.c \
	$S/dev/syscons/teken/teken.c $S/dev/uart/uart_cpu_i386.c \
	$S/i386/acpica/OsdEnvironment.c $S/i386/acpica/acpi_machdep.c \
	$S/i386/acpica/acpi_wakeup.c $S/i386/acpica/madt.c \
	$S/i386/cpufreq/est.c $S/i386/cpufreq/hwpstate.c \
	$S/i386/cpufreq/p4tcc.c $S/i386/cpufreq/powernow.c \
	$S/i386/cpufreq/smist.c $S/i386/i386/atomic.c \
	$S/i386/i386/autoconf.c $S/i386/i386/bios.c \
	$S/i386/i386/busdma_machdep.c $S/i386/i386/dump_machdep.c \
	$S/i386/i386/elf_machdep.c $S/i386/i386/i686_mem.c \
	$S/i386/i386/identcpu.c $S/i386/i386/in_cksum.c \
	$S/i386/i386/initcpu.c $S/i386/i386/intr_machdep.c \
	$S/i386/i386/io.c $S/i386/i386/io_apic.c $S/i386/i386/k6_mem.c \
	$S/i386/i386/legacy.c $S/i386/i386/local_apic.c \
	$S/i386/i386/machdep.c $S/i386/i386/mca.c $S/i386/i386/mem.c \
	$S/i386/i386/minidump_machdep.c $S/i386/i386/mp_clock.c \
	$S/i386/i386/mp_machdep.c $S/i386/i386/mptable.c \
	$S/i386/i386/mptable_pci.c $S/i386/i386/msi.c \
	$S/i386/i386/nexus.c $S/i386/i386/pmap.c \
	$S/i386/i386/ptrace_machdep.c $S/i386/i386/stack_machdep.c \
	$S/i386/i386/sys_machdep.c $S/i386/i386/trap.c \
	$S/i386/i386/tsc.c $S/i386/i386/uio_machdep.c \
	$S/i386/i386/vm86.c $S/i386/i386/vm_machdep.c \
	$S/i386/isa/atpic.c $S/i386/isa/clock.c $S/i386/isa/elcr.c \
	$S/i386/isa/elink.c $S/i386/isa/isa.c $S/i386/isa/isa_dma.c \
	$S/i386/isa/nmi.c $S/i386/isa/npx.c $S/i386/isa/pmtimer.c \
	$S/i386/pci/pci_bus.c $S/i386/pci/pci_cfgreg.c \
	$S/i386/pci/pci_pir.c $S/isa/atrtc.c $S/isa/syscons_isa.c \
	$S/isa/vga_isa.c $S/libkern/divdi3.c $S/libkern/ffsl.c \
	$S/libkern/flsl.c $S/libkern/memmove.c $S/libkern/memset.c \
	$S/libkern/moddi3.c $S/libkern/qdivrem.c $S/libkern/ucmpdi2.c \
	$S/libkern/udivdi3.c $S/libkern/umoddi3.c 

SFILES=$S/i386/i386/bioscall.s $S/i386/i386/exception.s \
	$S/i386/i386/locore.s $S/i386/i386/mpboot.s \
	$S/i386/i386/support.s $S/i386/i386/swtch.s 

MFILES=$S/dev/agp/agp_if.m $S/dev/ata/ata_if.m $S/dev/eisa/eisa_if.m \
	$S/dev/mii/miibus_if.m $S/dev/mmc/mmcbr_if.m \
	$S/dev/mmc/mmcbus_if.m $S/dev/pccard/card_if.m \
	$S/dev/pccard/power_if.m $S/dev/pci/pci_if.m \
	$S/dev/pci/pcib_if.m $S/dev/ppbus/ppbus_if.m \
	$S/dev/uart/uart_if.m $S/dev/usb/usb_if.m \
	$S/geom/part/g_part_if.m $S/isa/isa_if.m $S/kern/bus_if.m \
	$S/kern/clock_if.m $S/kern/cpufreq_if.m $S/kern/device_if.m \
	$S/kern/linker_if.m $S/kern/serdev_if.m $S/dev/acpica/acpi_if.m \
	$S/dev/acpi_support/acpi_wmi_if.m 

CLEAN=acpi_quirks.h aicasm* y.tab.h aic7xxx_seq.h aic7xxx_reg.h \
	aic7xxx_reg_print.c aic79xx_seq.h aic79xx_reg.h \
	aic79xx_reg_print.c miidevs.h pccarddevs.h teken_state.h \
	usbdevs.h usbdevs_data.h \
	acpi_wakecode.h acpi_wakecode.o acpi_wakecode.bin 

acpi_quirks.h: $S/tools/acpi_quirks2h.awk $S/dev/acpica/acpi_quirks
	${AWK} -f $S/tools/acpi_quirks2h.awk $S/dev/acpica/acpi_quirks

aicasm: $S/dev/aic7xxx/aicasm/*.[chyl]
	CC='${CC}' ${MAKE} -f $S/dev/aic7xxx/aicasm/Makefile MAKESRCPATH=$S/dev/aic7xxx/aicasm

aic7xxx_seq.h: $S/dev/aic7xxx/aic7xxx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic7xxx_seq.h -r aic7xxx_reg.h -p aic7xxx_reg_print.c -i $S/dev/aic7xxx/aic7xxx_osm.h $S/dev/aic7xxx/aic7xxx.seq

aic7xxx_reg.h: $S/dev/aic7xxx/aic7xxx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic7xxx_seq.h -r aic7xxx_reg.h -p aic7xxx_reg_print.c -i $S/dev/aic7xxx/aic7xxx_osm.h $S/dev/aic7xxx/aic7xxx.seq

aic7xxx_reg_print.c: $S/dev/aic7xxx/aic7xxx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic7xxx_seq.h -r aic7xxx_reg.h -p aic7xxx_reg_print.c -i $S/dev/aic7xxx/aic7xxx_osm.h $S/dev/aic7xxx/aic7xxx.seq

aic7xxx_reg_print.o: 
	${NORMAL_C}

aic79xx_seq.h: $S/dev/aic7xxx/aic79xx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic79xx_seq.h -r aic79xx_reg.h -p aic79xx_reg_print.c -i $S/dev/aic7xxx/aic79xx_osm.h $S/dev/aic7xxx/aic79xx.seq

aic79xx_reg.h: $S/dev/aic7xxx/aic79xx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic79xx_seq.h -r aic79xx_reg.h -p aic79xx_reg_print.c -i $S/dev/aic7xxx/aic79xx_osm.h $S/dev/aic7xxx/aic79xx.seq

aic79xx_reg_print.c: $S/dev/aic7xxx/aic79xx.{reg,seq} $S/cam/scsi/scsi_message.h aicasm
	./aicasm ${INCLUDES} -I$S/cam/scsi -I$S/dev/aic7xxx -o aic79xx_seq.h -r aic79xx_reg.h -p aic79xx_reg_print.c -i $S/dev/aic7xxx/aic79xx_osm.h $S/dev/aic7xxx/aic79xx.seq

aic79xx_reg_print.o: 
	${NORMAL_C}

miidevs.h: $S/tools/miidevs2h.awk $S/dev/mii/miidevs
	${AWK} -f $S/tools/miidevs2h.awk $S/dev/mii/miidevs

pccarddevs.h: $S/tools/pccarddevs2h.awk $S/dev/pccard/pccarddevs
	${AWK} -f $S/tools/pccarddevs2h.awk $S/dev/pccard/pccarddevs

teken_state.h: $S/dev/syscons/teken/gensequences $S/dev/syscons/teken/sequences
	${AWK} -f $S/dev/syscons/teken/gensequences $S/dev/syscons/teken/sequences > teken_state.h

usbdevs.h: $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs
	${AWK} -f $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs -h

usbdevs_data.h: $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs
	${AWK} -f $S/tools/usbdevs2h.awk $S/dev/usb/usbdevs -d

cam.ln: $S/cam/cam.c
	${NORMAL_LINT}

cam.o: $S/cam/cam.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cam_periph.ln: $S/cam/cam_periph.c
	${NORMAL_LINT}

cam_periph.o: $S/cam/cam_periph.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cam_queue.ln: $S/cam/cam_queue.c
	${NORMAL_LINT}

cam_queue.o: $S/cam/cam_queue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cam_sim.ln: $S/cam/cam_sim.c
	${NORMAL_LINT}

cam_sim.o: $S/cam/cam_sim.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cam_xpt.ln: $S/cam/cam_xpt.c
	${NORMAL_LINT}

cam_xpt.o: $S/cam/cam_xpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata_all.ln: $S/cam/ata/ata_all.c
	${NORMAL_LINT}

ata_all.o: $S/cam/ata/ata_all.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata_xpt.ln: $S/cam/ata/ata_xpt.c
	${NORMAL_LINT}

ata_xpt.o: $S/cam/ata/ata_xpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_xpt.ln: $S/cam/scsi/scsi_xpt.c
	${NORMAL_LINT}

scsi_xpt.o: $S/cam/scsi/scsi_xpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_all.ln: $S/cam/scsi/scsi_all.c
	${NORMAL_LINT}

scsi_all.o: $S/cam/scsi/scsi_all.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_cd.ln: $S/cam/scsi/scsi_cd.c
	${NORMAL_LINT}

scsi_cd.o: $S/cam/scsi/scsi_cd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_ch.ln: $S/cam/scsi/scsi_ch.c
	${NORMAL_LINT}

scsi_ch.o: $S/cam/scsi/scsi_ch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata_da.ln: $S/cam/ata/ata_da.c
	${NORMAL_LINT}

ata_da.o: $S/cam/ata/ata_da.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_da.ln: $S/cam/scsi/scsi_da.c
	${NORMAL_LINT}

scsi_da.o: $S/cam/scsi/scsi_da.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_low.ln: $S/cam/scsi/scsi_low.c
	${NORMAL_LINT}

scsi_low.o: $S/cam/scsi/scsi_low.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_low_pisa.ln: $S/cam/scsi/scsi_low_pisa.c
	${NORMAL_LINT}

scsi_low_pisa.o: $S/cam/scsi/scsi_low_pisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_pass.ln: $S/cam/scsi/scsi_pass.c
	${NORMAL_LINT}

scsi_pass.o: $S/cam/scsi/scsi_pass.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_sa.ln: $S/cam/scsi/scsi_sa.c
	${NORMAL_LINT}

scsi_sa.o: $S/cam/scsi/scsi_sa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scsi_ses.ln: $S/cam/scsi/scsi_ses.c
	${NORMAL_LINT}

scsi_ses.o: $S/cam/scsi/scsi_ses.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsfield.ln: $S/contrib/dev/acpica/dispatcher/dsfield.c
	${NORMAL_LINT}

dsfield.o: $S/contrib/dev/acpica/dispatcher/dsfield.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsinit.ln: $S/contrib/dev/acpica/dispatcher/dsinit.c
	${NORMAL_LINT}

dsinit.o: $S/contrib/dev/acpica/dispatcher/dsinit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsmethod.ln: $S/contrib/dev/acpica/dispatcher/dsmethod.c
	${NORMAL_LINT}

dsmethod.o: $S/contrib/dev/acpica/dispatcher/dsmethod.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsmthdat.ln: $S/contrib/dev/acpica/dispatcher/dsmthdat.c
	${NORMAL_LINT}

dsmthdat.o: $S/contrib/dev/acpica/dispatcher/dsmthdat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsobject.ln: $S/contrib/dev/acpica/dispatcher/dsobject.c
	${NORMAL_LINT}

dsobject.o: $S/contrib/dev/acpica/dispatcher/dsobject.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsopcode.ln: $S/contrib/dev/acpica/dispatcher/dsopcode.c
	${NORMAL_LINT}

dsopcode.o: $S/contrib/dev/acpica/dispatcher/dsopcode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dsutils.ln: $S/contrib/dev/acpica/dispatcher/dsutils.c
	${NORMAL_LINT}

dsutils.o: $S/contrib/dev/acpica/dispatcher/dsutils.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dswexec.ln: $S/contrib/dev/acpica/dispatcher/dswexec.c
	${NORMAL_LINT}

dswexec.o: $S/contrib/dev/acpica/dispatcher/dswexec.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dswload.ln: $S/contrib/dev/acpica/dispatcher/dswload.c
	${NORMAL_LINT}

dswload.o: $S/contrib/dev/acpica/dispatcher/dswload.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dswscope.ln: $S/contrib/dev/acpica/dispatcher/dswscope.c
	${NORMAL_LINT}

dswscope.o: $S/contrib/dev/acpica/dispatcher/dswscope.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dswstate.ln: $S/contrib/dev/acpica/dispatcher/dswstate.c
	${NORMAL_LINT}

dswstate.o: $S/contrib/dev/acpica/dispatcher/dswstate.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evevent.ln: $S/contrib/dev/acpica/events/evevent.c
	${NORMAL_LINT}

evevent.o: $S/contrib/dev/acpica/events/evevent.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evgpe.ln: $S/contrib/dev/acpica/events/evgpe.c
	${NORMAL_LINT}

evgpe.o: $S/contrib/dev/acpica/events/evgpe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evgpeblk.ln: $S/contrib/dev/acpica/events/evgpeblk.c
	${NORMAL_LINT}

evgpeblk.o: $S/contrib/dev/acpica/events/evgpeblk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evmisc.ln: $S/contrib/dev/acpica/events/evmisc.c
	${NORMAL_LINT}

evmisc.o: $S/contrib/dev/acpica/events/evmisc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evregion.ln: $S/contrib/dev/acpica/events/evregion.c
	${NORMAL_LINT}

evregion.o: $S/contrib/dev/acpica/events/evregion.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evrgnini.ln: $S/contrib/dev/acpica/events/evrgnini.c
	${NORMAL_LINT}

evrgnini.o: $S/contrib/dev/acpica/events/evrgnini.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evsci.ln: $S/contrib/dev/acpica/events/evsci.c
	${NORMAL_LINT}

evsci.o: $S/contrib/dev/acpica/events/evsci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evxface.ln: $S/contrib/dev/acpica/events/evxface.c
	${NORMAL_LINT}

evxface.o: $S/contrib/dev/acpica/events/evxface.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evxfevnt.ln: $S/contrib/dev/acpica/events/evxfevnt.c
	${NORMAL_LINT}

evxfevnt.o: $S/contrib/dev/acpica/events/evxfevnt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

evxfregn.ln: $S/contrib/dev/acpica/events/evxfregn.c
	${NORMAL_LINT}

evxfregn.o: $S/contrib/dev/acpica/events/evxfregn.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exconfig.ln: $S/contrib/dev/acpica/executer/exconfig.c
	${NORMAL_LINT}

exconfig.o: $S/contrib/dev/acpica/executer/exconfig.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exconvrt.ln: $S/contrib/dev/acpica/executer/exconvrt.c
	${NORMAL_LINT}

exconvrt.o: $S/contrib/dev/acpica/executer/exconvrt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

excreate.ln: $S/contrib/dev/acpica/executer/excreate.c
	${NORMAL_LINT}

excreate.o: $S/contrib/dev/acpica/executer/excreate.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exdump.ln: $S/contrib/dev/acpica/executer/exdump.c
	${NORMAL_LINT}

exdump.o: $S/contrib/dev/acpica/executer/exdump.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exfield.ln: $S/contrib/dev/acpica/executer/exfield.c
	${NORMAL_LINT}

exfield.o: $S/contrib/dev/acpica/executer/exfield.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exfldio.ln: $S/contrib/dev/acpica/executer/exfldio.c
	${NORMAL_LINT}

exfldio.o: $S/contrib/dev/acpica/executer/exfldio.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exmisc.ln: $S/contrib/dev/acpica/executer/exmisc.c
	${NORMAL_LINT}

exmisc.o: $S/contrib/dev/acpica/executer/exmisc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exmutex.ln: $S/contrib/dev/acpica/executer/exmutex.c
	${NORMAL_LINT}

exmutex.o: $S/contrib/dev/acpica/executer/exmutex.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exnames.ln: $S/contrib/dev/acpica/executer/exnames.c
	${NORMAL_LINT}

exnames.o: $S/contrib/dev/acpica/executer/exnames.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exoparg1.ln: $S/contrib/dev/acpica/executer/exoparg1.c
	${NORMAL_LINT}

exoparg1.o: $S/contrib/dev/acpica/executer/exoparg1.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exoparg2.ln: $S/contrib/dev/acpica/executer/exoparg2.c
	${NORMAL_LINT}

exoparg2.o: $S/contrib/dev/acpica/executer/exoparg2.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exoparg3.ln: $S/contrib/dev/acpica/executer/exoparg3.c
	${NORMAL_LINT}

exoparg3.o: $S/contrib/dev/acpica/executer/exoparg3.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exoparg6.ln: $S/contrib/dev/acpica/executer/exoparg6.c
	${NORMAL_LINT}

exoparg6.o: $S/contrib/dev/acpica/executer/exoparg6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exprep.ln: $S/contrib/dev/acpica/executer/exprep.c
	${NORMAL_LINT}

exprep.o: $S/contrib/dev/acpica/executer/exprep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exregion.ln: $S/contrib/dev/acpica/executer/exregion.c
	${NORMAL_LINT}

exregion.o: $S/contrib/dev/acpica/executer/exregion.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exresnte.ln: $S/contrib/dev/acpica/executer/exresnte.c
	${NORMAL_LINT}

exresnte.o: $S/contrib/dev/acpica/executer/exresnte.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exresolv.ln: $S/contrib/dev/acpica/executer/exresolv.c
	${NORMAL_LINT}

exresolv.o: $S/contrib/dev/acpica/executer/exresolv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exresop.ln: $S/contrib/dev/acpica/executer/exresop.c
	${NORMAL_LINT}

exresop.o: $S/contrib/dev/acpica/executer/exresop.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exstore.ln: $S/contrib/dev/acpica/executer/exstore.c
	${NORMAL_LINT}

exstore.o: $S/contrib/dev/acpica/executer/exstore.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exstoren.ln: $S/contrib/dev/acpica/executer/exstoren.c
	${NORMAL_LINT}

exstoren.o: $S/contrib/dev/acpica/executer/exstoren.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exstorob.ln: $S/contrib/dev/acpica/executer/exstorob.c
	${NORMAL_LINT}

exstorob.o: $S/contrib/dev/acpica/executer/exstorob.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exsystem.ln: $S/contrib/dev/acpica/executer/exsystem.c
	${NORMAL_LINT}

exsystem.o: $S/contrib/dev/acpica/executer/exsystem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exutils.ln: $S/contrib/dev/acpica/executer/exutils.c
	${NORMAL_LINT}

exutils.o: $S/contrib/dev/acpica/executer/exutils.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwacpi.ln: $S/contrib/dev/acpica/hardware/hwacpi.c
	${NORMAL_LINT}

hwacpi.o: $S/contrib/dev/acpica/hardware/hwacpi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwgpe.ln: $S/contrib/dev/acpica/hardware/hwgpe.c
	${NORMAL_LINT}

hwgpe.o: $S/contrib/dev/acpica/hardware/hwgpe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwregs.ln: $S/contrib/dev/acpica/hardware/hwregs.c
	${NORMAL_LINT}

hwregs.o: $S/contrib/dev/acpica/hardware/hwregs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwsleep.ln: $S/contrib/dev/acpica/hardware/hwsleep.c
	${NORMAL_LINT}

hwsleep.o: $S/contrib/dev/acpica/hardware/hwsleep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwtimer.ln: $S/contrib/dev/acpica/hardware/hwtimer.c
	${NORMAL_LINT}

hwtimer.o: $S/contrib/dev/acpica/hardware/hwtimer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwvalid.ln: $S/contrib/dev/acpica/hardware/hwvalid.c
	${NORMAL_LINT}

hwvalid.o: $S/contrib/dev/acpica/hardware/hwvalid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwxface.ln: $S/contrib/dev/acpica/hardware/hwxface.c
	${NORMAL_LINT}

hwxface.o: $S/contrib/dev/acpica/hardware/hwxface.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsaccess.ln: $S/contrib/dev/acpica/namespace/nsaccess.c
	${NORMAL_LINT}

nsaccess.o: $S/contrib/dev/acpica/namespace/nsaccess.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsalloc.ln: $S/contrib/dev/acpica/namespace/nsalloc.c
	${NORMAL_LINT}

nsalloc.o: $S/contrib/dev/acpica/namespace/nsalloc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsdump.ln: $S/contrib/dev/acpica/namespace/nsdump.c
	${NORMAL_LINT}

nsdump.o: $S/contrib/dev/acpica/namespace/nsdump.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nseval.ln: $S/contrib/dev/acpica/namespace/nseval.c
	${NORMAL_LINT}

nseval.o: $S/contrib/dev/acpica/namespace/nseval.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsinit.ln: $S/contrib/dev/acpica/namespace/nsinit.c
	${NORMAL_LINT}

nsinit.o: $S/contrib/dev/acpica/namespace/nsinit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsload.ln: $S/contrib/dev/acpica/namespace/nsload.c
	${NORMAL_LINT}

nsload.o: $S/contrib/dev/acpica/namespace/nsload.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsnames.ln: $S/contrib/dev/acpica/namespace/nsnames.c
	${NORMAL_LINT}

nsnames.o: $S/contrib/dev/acpica/namespace/nsnames.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsobject.ln: $S/contrib/dev/acpica/namespace/nsobject.c
	${NORMAL_LINT}

nsobject.o: $S/contrib/dev/acpica/namespace/nsobject.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsparse.ln: $S/contrib/dev/acpica/namespace/nsparse.c
	${NORMAL_LINT}

nsparse.o: $S/contrib/dev/acpica/namespace/nsparse.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nspredef.ln: $S/contrib/dev/acpica/namespace/nspredef.c
	${NORMAL_LINT}

nspredef.o: $S/contrib/dev/acpica/namespace/nspredef.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nssearch.ln: $S/contrib/dev/acpica/namespace/nssearch.c
	${NORMAL_LINT}

nssearch.o: $S/contrib/dev/acpica/namespace/nssearch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsutils.ln: $S/contrib/dev/acpica/namespace/nsutils.c
	${NORMAL_LINT}

nsutils.o: $S/contrib/dev/acpica/namespace/nsutils.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nswalk.ln: $S/contrib/dev/acpica/namespace/nswalk.c
	${NORMAL_LINT}

nswalk.o: $S/contrib/dev/acpica/namespace/nswalk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsxfeval.ln: $S/contrib/dev/acpica/namespace/nsxfeval.c
	${NORMAL_LINT}

nsxfeval.o: $S/contrib/dev/acpica/namespace/nsxfeval.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsxfname.ln: $S/contrib/dev/acpica/namespace/nsxfname.c
	${NORMAL_LINT}

nsxfname.o: $S/contrib/dev/acpica/namespace/nsxfname.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsxfobj.ln: $S/contrib/dev/acpica/namespace/nsxfobj.c
	${NORMAL_LINT}

nsxfobj.o: $S/contrib/dev/acpica/namespace/nsxfobj.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psargs.ln: $S/contrib/dev/acpica/parser/psargs.c
	${NORMAL_LINT}

psargs.o: $S/contrib/dev/acpica/parser/psargs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psloop.ln: $S/contrib/dev/acpica/parser/psloop.c
	${NORMAL_LINT}

psloop.o: $S/contrib/dev/acpica/parser/psloop.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psopcode.ln: $S/contrib/dev/acpica/parser/psopcode.c
	${NORMAL_LINT}

psopcode.o: $S/contrib/dev/acpica/parser/psopcode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psparse.ln: $S/contrib/dev/acpica/parser/psparse.c
	${NORMAL_LINT}

psparse.o: $S/contrib/dev/acpica/parser/psparse.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psscope.ln: $S/contrib/dev/acpica/parser/psscope.c
	${NORMAL_LINT}

psscope.o: $S/contrib/dev/acpica/parser/psscope.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pstree.ln: $S/contrib/dev/acpica/parser/pstree.c
	${NORMAL_LINT}

pstree.o: $S/contrib/dev/acpica/parser/pstree.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psutils.ln: $S/contrib/dev/acpica/parser/psutils.c
	${NORMAL_LINT}

psutils.o: $S/contrib/dev/acpica/parser/psutils.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pswalk.ln: $S/contrib/dev/acpica/parser/pswalk.c
	${NORMAL_LINT}

pswalk.o: $S/contrib/dev/acpica/parser/pswalk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psxface.ln: $S/contrib/dev/acpica/parser/psxface.c
	${NORMAL_LINT}

psxface.o: $S/contrib/dev/acpica/parser/psxface.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsaddr.ln: $S/contrib/dev/acpica/resources/rsaddr.c
	${NORMAL_LINT}

rsaddr.o: $S/contrib/dev/acpica/resources/rsaddr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rscalc.ln: $S/contrib/dev/acpica/resources/rscalc.c
	${NORMAL_LINT}

rscalc.o: $S/contrib/dev/acpica/resources/rscalc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rscreate.ln: $S/contrib/dev/acpica/resources/rscreate.c
	${NORMAL_LINT}

rscreate.o: $S/contrib/dev/acpica/resources/rscreate.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsdump.ln: $S/contrib/dev/acpica/resources/rsdump.c
	${NORMAL_LINT}

rsdump.o: $S/contrib/dev/acpica/resources/rsdump.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsinfo.ln: $S/contrib/dev/acpica/resources/rsinfo.c
	${NORMAL_LINT}

rsinfo.o: $S/contrib/dev/acpica/resources/rsinfo.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsio.ln: $S/contrib/dev/acpica/resources/rsio.c
	${NORMAL_LINT}

rsio.o: $S/contrib/dev/acpica/resources/rsio.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsirq.ln: $S/contrib/dev/acpica/resources/rsirq.c
	${NORMAL_LINT}

rsirq.o: $S/contrib/dev/acpica/resources/rsirq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rslist.ln: $S/contrib/dev/acpica/resources/rslist.c
	${NORMAL_LINT}

rslist.o: $S/contrib/dev/acpica/resources/rslist.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsmemory.ln: $S/contrib/dev/acpica/resources/rsmemory.c
	${NORMAL_LINT}

rsmemory.o: $S/contrib/dev/acpica/resources/rsmemory.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsmisc.ln: $S/contrib/dev/acpica/resources/rsmisc.c
	${NORMAL_LINT}

rsmisc.o: $S/contrib/dev/acpica/resources/rsmisc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsutils.ln: $S/contrib/dev/acpica/resources/rsutils.c
	${NORMAL_LINT}

rsutils.o: $S/contrib/dev/acpica/resources/rsutils.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rsxface.ln: $S/contrib/dev/acpica/resources/rsxface.c
	${NORMAL_LINT}

rsxface.o: $S/contrib/dev/acpica/resources/rsxface.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tbfadt.ln: $S/contrib/dev/acpica/tables/tbfadt.c
	${NORMAL_LINT}

tbfadt.o: $S/contrib/dev/acpica/tables/tbfadt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tbfind.ln: $S/contrib/dev/acpica/tables/tbfind.c
	${NORMAL_LINT}

tbfind.o: $S/contrib/dev/acpica/tables/tbfind.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tbinstal.ln: $S/contrib/dev/acpica/tables/tbinstal.c
	${NORMAL_LINT}

tbinstal.o: $S/contrib/dev/acpica/tables/tbinstal.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tbutils.ln: $S/contrib/dev/acpica/tables/tbutils.c
	${NORMAL_LINT}

tbutils.o: $S/contrib/dev/acpica/tables/tbutils.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tbxface.ln: $S/contrib/dev/acpica/tables/tbxface.c
	${NORMAL_LINT}

tbxface.o: $S/contrib/dev/acpica/tables/tbxface.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tbxfroot.ln: $S/contrib/dev/acpica/tables/tbxfroot.c
	${NORMAL_LINT}

tbxfroot.o: $S/contrib/dev/acpica/tables/tbxfroot.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utalloc.ln: $S/contrib/dev/acpica/utilities/utalloc.c
	${NORMAL_LINT}

utalloc.o: $S/contrib/dev/acpica/utilities/utalloc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utcache.ln: $S/contrib/dev/acpica/utilities/utcache.c
	${NORMAL_LINT}

utcache.o: $S/contrib/dev/acpica/utilities/utcache.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utcopy.ln: $S/contrib/dev/acpica/utilities/utcopy.c
	${NORMAL_LINT}

utcopy.o: $S/contrib/dev/acpica/utilities/utcopy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utdebug.ln: $S/contrib/dev/acpica/utilities/utdebug.c
	${NORMAL_LINT}

utdebug.o: $S/contrib/dev/acpica/utilities/utdebug.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utdelete.ln: $S/contrib/dev/acpica/utilities/utdelete.c
	${NORMAL_LINT}

utdelete.o: $S/contrib/dev/acpica/utilities/utdelete.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uteval.ln: $S/contrib/dev/acpica/utilities/uteval.c
	${NORMAL_LINT}

uteval.o: $S/contrib/dev/acpica/utilities/uteval.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utglobal.ln: $S/contrib/dev/acpica/utilities/utglobal.c
	${NORMAL_LINT}

utglobal.o: $S/contrib/dev/acpica/utilities/utglobal.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utinit.ln: $S/contrib/dev/acpica/utilities/utinit.c
	${NORMAL_LINT}

utinit.o: $S/contrib/dev/acpica/utilities/utinit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utlock.ln: $S/contrib/dev/acpica/utilities/utlock.c
	${NORMAL_LINT}

utlock.o: $S/contrib/dev/acpica/utilities/utlock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utmath.ln: $S/contrib/dev/acpica/utilities/utmath.c
	${NORMAL_LINT}

utmath.o: $S/contrib/dev/acpica/utilities/utmath.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utmisc.ln: $S/contrib/dev/acpica/utilities/utmisc.c
	${NORMAL_LINT}

utmisc.o: $S/contrib/dev/acpica/utilities/utmisc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utmutex.ln: $S/contrib/dev/acpica/utilities/utmutex.c
	${NORMAL_LINT}

utmutex.o: $S/contrib/dev/acpica/utilities/utmutex.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utobject.ln: $S/contrib/dev/acpica/utilities/utobject.c
	${NORMAL_LINT}

utobject.o: $S/contrib/dev/acpica/utilities/utobject.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utresrc.ln: $S/contrib/dev/acpica/utilities/utresrc.c
	${NORMAL_LINT}

utresrc.o: $S/contrib/dev/acpica/utilities/utresrc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utstate.ln: $S/contrib/dev/acpica/utilities/utstate.c
	${NORMAL_LINT}

utstate.o: $S/contrib/dev/acpica/utilities/utstate.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

utxface.ln: $S/contrib/dev/acpica/utilities/utxface.c
	${NORMAL_LINT}

utxface.o: $S/contrib/dev/acpica/utilities/utxface.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rijndael-alg-fst.ln: $S/crypto/rijndael/rijndael-alg-fst.c
	${NORMAL_LINT}

rijndael-alg-fst.o: $S/crypto/rijndael/rijndael-alg-fst.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rijndael-api-fst.ln: $S/crypto/rijndael/rijndael-api-fst.c
	${NORMAL_LINT}

rijndael-api-fst.o: $S/crypto/rijndael/rijndael-api-fst.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rijndael-api.ln: $S/crypto/rijndael/rijndael-api.c
	${NORMAL_LINT}

rijndael-api.o: $S/crypto/rijndael/rijndael-api.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sha1.ln: $S/crypto/sha1.c
	${NORMAL_LINT}

sha1.o: $S/crypto/sha1.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sha2.ln: $S/crypto/sha2/sha2.c
	${NORMAL_LINT}

sha2.o: $S/crypto/sha2/sha2.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aac.ln: $S/dev/aac/aac.c
	${NORMAL_LINT}

aac.o: $S/dev/aac/aac.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aac_cam.ln: $S/dev/aac/aac_cam.c
	${NORMAL_LINT}

aac_cam.o: $S/dev/aac/aac_cam.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aac_debug.ln: $S/dev/aac/aac_debug.c
	${NORMAL_LINT}

aac_debug.o: $S/dev/aac/aac_debug.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aac_disk.ln: $S/dev/aac/aac_disk.c
	${NORMAL_LINT}

aac_disk.o: $S/dev/aac/aac_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aac_pci.ln: $S/dev/aac/aac_pci.c
	${NORMAL_LINT}

aac_pci.o: $S/dev/aac/aac_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdDebug.ln: $S/dev/acpica/Osd/OsdDebug.c
	${NORMAL_LINT}

OsdDebug.o: $S/dev/acpica/Osd/OsdDebug.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdHardware.ln: $S/dev/acpica/Osd/OsdHardware.c
	${NORMAL_LINT}

OsdHardware.o: $S/dev/acpica/Osd/OsdHardware.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdInterrupt.ln: $S/dev/acpica/Osd/OsdInterrupt.c
	${NORMAL_LINT}

OsdInterrupt.o: $S/dev/acpica/Osd/OsdInterrupt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdMemory.ln: $S/dev/acpica/Osd/OsdMemory.c
	${NORMAL_LINT}

OsdMemory.o: $S/dev/acpica/Osd/OsdMemory.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdSchedule.ln: $S/dev/acpica/Osd/OsdSchedule.c
	${NORMAL_LINT}

OsdSchedule.o: $S/dev/acpica/Osd/OsdSchedule.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdStream.ln: $S/dev/acpica/Osd/OsdStream.c
	${NORMAL_LINT}

OsdStream.o: $S/dev/acpica/Osd/OsdStream.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdSynch.ln: $S/dev/acpica/Osd/OsdSynch.c
	${NORMAL_LINT}

OsdSynch.o: $S/dev/acpica/Osd/OsdSynch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdTable.ln: $S/dev/acpica/Osd/OsdTable.c
	${NORMAL_LINT}

OsdTable.o: $S/dev/acpica/Osd/OsdTable.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi.ln: $S/dev/acpica/acpi.c
	${NORMAL_LINT}

acpi.o: $S/dev/acpica/acpi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_acad.ln: $S/dev/acpica/acpi_acad.c
	${NORMAL_LINT}

acpi_acad.o: $S/dev/acpica/acpi_acad.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_battery.ln: $S/dev/acpica/acpi_battery.c
	${NORMAL_LINT}

acpi_battery.o: $S/dev/acpica/acpi_battery.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_button.ln: $S/dev/acpica/acpi_button.c
	${NORMAL_LINT}

acpi_button.o: $S/dev/acpica/acpi_button.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_cmbat.ln: $S/dev/acpica/acpi_cmbat.c
	${NORMAL_LINT}

acpi_cmbat.o: $S/dev/acpica/acpi_cmbat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_cpu.ln: $S/dev/acpica/acpi_cpu.c
	${NORMAL_LINT}

acpi_cpu.o: $S/dev/acpica/acpi_cpu.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_ec.ln: $S/dev/acpica/acpi_ec.c
	${NORMAL_LINT}

acpi_ec.o: $S/dev/acpica/acpi_ec.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_hpet.ln: $S/dev/acpica/acpi_hpet.c
	${NORMAL_LINT}

acpi_hpet.o: $S/dev/acpica/acpi_hpet.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_isab.ln: $S/dev/acpica/acpi_isab.c
	${NORMAL_LINT}

acpi_isab.o: $S/dev/acpica/acpi_isab.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_lid.ln: $S/dev/acpica/acpi_lid.c
	${NORMAL_LINT}

acpi_lid.o: $S/dev/acpica/acpi_lid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_package.ln: $S/dev/acpica/acpi_package.c
	${NORMAL_LINT}

acpi_package.o: $S/dev/acpica/acpi_package.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_pci.ln: $S/dev/acpica/acpi_pci.c
	${NORMAL_LINT}

acpi_pci.o: $S/dev/acpica/acpi_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_pci_link.ln: $S/dev/acpica/acpi_pci_link.c
	${NORMAL_LINT}

acpi_pci_link.o: $S/dev/acpica/acpi_pci_link.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_pcib.ln: $S/dev/acpica/acpi_pcib.c
	${NORMAL_LINT}

acpi_pcib.o: $S/dev/acpica/acpi_pcib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_pcib_acpi.ln: $S/dev/acpica/acpi_pcib_acpi.c
	${NORMAL_LINT}

acpi_pcib_acpi.o: $S/dev/acpica/acpi_pcib_acpi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_pcib_pci.ln: $S/dev/acpica/acpi_pcib_pci.c
	${NORMAL_LINT}

acpi_pcib_pci.o: $S/dev/acpica/acpi_pcib_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_perf.ln: $S/dev/acpica/acpi_perf.c
	${NORMAL_LINT}

acpi_perf.o: $S/dev/acpica/acpi_perf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_powerres.ln: $S/dev/acpica/acpi_powerres.c
	${NORMAL_LINT}

acpi_powerres.o: $S/dev/acpica/acpi_powerres.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_quirk.ln: $S/dev/acpica/acpi_quirk.c
	${NORMAL_LINT}

acpi_quirk.o: $S/dev/acpica/acpi_quirk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_resource.ln: $S/dev/acpica/acpi_resource.c
	${NORMAL_LINT}

acpi_resource.o: $S/dev/acpica/acpi_resource.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_smbat.ln: $S/dev/acpica/acpi_smbat.c
	${NORMAL_LINT}

acpi_smbat.o: $S/dev/acpica/acpi_smbat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_thermal.ln: $S/dev/acpica/acpi_thermal.c
	${NORMAL_LINT}

acpi_thermal.o: $S/dev/acpica/acpi_thermal.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_throttle.ln: $S/dev/acpica/acpi_throttle.c
	${NORMAL_LINT}

acpi_throttle.o: $S/dev/acpica/acpi_throttle.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_timer.ln: $S/dev/acpica/acpi_timer.c
	${NORMAL_LINT}

acpi_timer.o: $S/dev/acpica/acpi_timer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

adv_eisa.ln: $S/dev/advansys/adv_eisa.c
	${NORMAL_LINT}

adv_eisa.o: $S/dev/advansys/adv_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

adv_pci.ln: $S/dev/advansys/adv_pci.c
	${NORMAL_LINT}

adv_pci.o: $S/dev/advansys/adv_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

advansys.ln: $S/dev/advansys/advansys.c
	${NORMAL_LINT}

advansys.o: $S/dev/advansys/advansys.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

advlib.ln: $S/dev/advansys/advlib.c
	${NORMAL_LINT}

advlib.o: $S/dev/advansys/advlib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

advmcode.ln: $S/dev/advansys/advmcode.c
	${NORMAL_LINT}

advmcode.o: $S/dev/advansys/advmcode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

adw_pci.ln: $S/dev/advansys/adw_pci.c
	${NORMAL_LINT}

adw_pci.o: $S/dev/advansys/adw_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

adwcam.ln: $S/dev/advansys/adwcam.c
	${NORMAL_LINT}

adwcam.o: $S/dev/advansys/adwcam.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

adwlib.ln: $S/dev/advansys/adwlib.c
	${NORMAL_LINT}

adwlib.o: $S/dev/advansys/adwlib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

adwmcode.ln: $S/dev/advansys/adwmcode.c
	${NORMAL_LINT}

adwmcode.o: $S/dev/advansys/adwmcode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ae.ln: $S/dev/ae/if_ae.c
	${NORMAL_LINT}

if_ae.o: $S/dev/ae/if_ae.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_age.ln: $S/dev/age/if_age.c
	${NORMAL_LINT}

if_age.o: $S/dev/age/if_age.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp.ln: $S/dev/agp/agp.c
	${NORMAL_LINT}

agp.o: $S/dev/agp/agp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_if.ln: $S/dev/agp/agp_if.m
	${NORMAL_LINT}

agp_if.o: $S/dev/agp/agp_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aha.ln: $S/dev/aha/aha.c
	${NORMAL_LINT}

aha.o: $S/dev/aha/aha.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aha_isa.ln: $S/dev/aha/aha_isa.c
	${NORMAL_LINT}

aha_isa.o: $S/dev/aha/aha_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ahb.ln: $S/dev/ahb/ahb.c
	${NORMAL_LINT}

ahb.o: $S/dev/ahb/ahb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic.ln: $S/dev/aic/aic.c
	${NORMAL_LINT}

aic.o: $S/dev/aic/aic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic_pccard.ln: $S/dev/aic/aic_pccard.c
	${NORMAL_LINT}

aic_pccard.o: $S/dev/aic/aic_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ahc_eisa.ln: $S/dev/aic7xxx/ahc_eisa.c
	${NORMAL_LINT}

ahc_eisa.o: $S/dev/aic7xxx/ahc_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ahc_isa.ln: $S/dev/aic7xxx/ahc_isa.c
	${NORMAL_LINT}

ahc_isa.o: $S/dev/aic7xxx/ahc_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ahc_pci.ln: $S/dev/aic7xxx/ahc_pci.c
	${NORMAL_LINT}

ahc_pci.o: $S/dev/aic7xxx/ahc_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ahd_pci.ln: $S/dev/aic7xxx/ahd_pci.c
	${NORMAL_LINT}

ahd_pci.o: $S/dev/aic7xxx/ahd_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic7770.ln: $S/dev/aic7xxx/aic7770.c
	${NORMAL_LINT}

aic7770.o: $S/dev/aic7xxx/aic7770.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic79xx.ln: $S/dev/aic7xxx/aic79xx.c
	${NORMAL_LINT}

aic79xx.o: $S/dev/aic7xxx/aic79xx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic79xx_osm.ln: $S/dev/aic7xxx/aic79xx_osm.c
	${NORMAL_LINT}

aic79xx_osm.o: $S/dev/aic7xxx/aic79xx_osm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic79xx_pci.ln: $S/dev/aic7xxx/aic79xx_pci.c
	${NORMAL_LINT}

aic79xx_pci.o: $S/dev/aic7xxx/aic79xx_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic7xxx.ln: $S/dev/aic7xxx/aic7xxx.c
	${NORMAL_LINT}

aic7xxx.o: $S/dev/aic7xxx/aic7xxx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic7xxx_93cx6.ln: $S/dev/aic7xxx/aic7xxx_93cx6.c
	${NORMAL_LINT}

aic7xxx_93cx6.o: $S/dev/aic7xxx/aic7xxx_93cx6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic7xxx_osm.ln: $S/dev/aic7xxx/aic7xxx_osm.c
	${NORMAL_LINT}

aic7xxx_osm.o: $S/dev/aic7xxx/aic7xxx_osm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic7xxx_pci.ln: $S/dev/aic7xxx/aic7xxx_pci.c
	${NORMAL_LINT}

aic7xxx_pci.o: $S/dev/aic7xxx/aic7xxx_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_alc.ln: $S/dev/alc/if_alc.c
	${NORMAL_LINT}

if_alc.o: $S/dev/alc/if_alc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ale.ln: $S/dev/ale/if_ale.c
	${NORMAL_LINT}

if_ale.o: $S/dev/ale/if_ale.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

amd.ln: $S/dev/amd/amd.c
	${NORMAL_LINT}

amd.o: $S/dev/amd/amd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

amr.ln: $S/dev/amr/amr.c
	${NORMAL_LINT}

amr.o: $S/dev/amr/amr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

amr_disk.ln: $S/dev/amr/amr_disk.c
	${NORMAL_LINT}

amr_disk.o: $S/dev/amr/amr_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

amr_pci.ln: $S/dev/amr/amr_pci.c
	${NORMAL_LINT}

amr_pci.o: $S/dev/amr/amr_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_an.ln: $S/dev/an/if_an.c
	${NORMAL_LINT}

if_an.o: $S/dev/an/if_an.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_an_isa.ln: $S/dev/an/if_an_isa.c
	${NORMAL_LINT}

if_an_isa.o: $S/dev/an/if_an_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_an_pccard.ln: $S/dev/an/if_an_pccard.c
	${NORMAL_LINT}

if_an_pccard.o: $S/dev/an/if_an_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_an_pci.ln: $S/dev/an/if_an_pci.c
	${NORMAL_LINT}

if_an_pci.o: $S/dev/an/if_an_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

asr.ln: $S/dev/asr/asr.c
	${NORMAL_LINT}

asr.o: $S/dev/asr/asr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata_if.ln: $S/dev/ata/ata_if.m
	${NORMAL_LINT}

ata_if.o: $S/dev/ata/ata_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-all.ln: $S/dev/ata/ata-all.c
	${NORMAL_LINT}

ata-all.o: $S/dev/ata/ata-all.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-dma.ln: $S/dev/ata/ata-dma.c
	${NORMAL_LINT}

ata-dma.o: $S/dev/ata/ata-dma.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-lowlevel.ln: $S/dev/ata/ata-lowlevel.c
	${NORMAL_LINT}

ata-lowlevel.o: $S/dev/ata/ata-lowlevel.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-queue.ln: $S/dev/ata/ata-queue.c
	${NORMAL_LINT}

ata-queue.o: $S/dev/ata/ata-queue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-sata.ln: $S/dev/ata/ata-sata.c
	${NORMAL_LINT}

ata-sata.o: $S/dev/ata/ata-sata.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-card.ln: $S/dev/ata/ata-card.c
	${NORMAL_LINT}

ata-card.o: $S/dev/ata/ata-card.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-isa.ln: $S/dev/ata/ata-isa.c
	${NORMAL_LINT}

ata-isa.o: $S/dev/ata/ata-isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-pci.ln: $S/dev/ata/ata-pci.c
	${NORMAL_LINT}

ata-pci.o: $S/dev/ata/ata-pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-ahci.ln: $S/dev/ata/chipsets/ata-ahci.c
	${NORMAL_LINT}

ata-ahci.o: $S/dev/ata/chipsets/ata-ahci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-acard.ln: $S/dev/ata/chipsets/ata-acard.c
	${NORMAL_LINT}

ata-acard.o: $S/dev/ata/chipsets/ata-acard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-acerlabs.ln: $S/dev/ata/chipsets/ata-acerlabs.c
	${NORMAL_LINT}

ata-acerlabs.o: $S/dev/ata/chipsets/ata-acerlabs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-adaptec.ln: $S/dev/ata/chipsets/ata-adaptec.c
	${NORMAL_LINT}

ata-adaptec.o: $S/dev/ata/chipsets/ata-adaptec.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-amd.ln: $S/dev/ata/chipsets/ata-amd.c
	${NORMAL_LINT}

ata-amd.o: $S/dev/ata/chipsets/ata-amd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-ati.ln: $S/dev/ata/chipsets/ata-ati.c
	${NORMAL_LINT}

ata-ati.o: $S/dev/ata/chipsets/ata-ati.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-cenatek.ln: $S/dev/ata/chipsets/ata-cenatek.c
	${NORMAL_LINT}

ata-cenatek.o: $S/dev/ata/chipsets/ata-cenatek.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-cypress.ln: $S/dev/ata/chipsets/ata-cypress.c
	${NORMAL_LINT}

ata-cypress.o: $S/dev/ata/chipsets/ata-cypress.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-cyrix.ln: $S/dev/ata/chipsets/ata-cyrix.c
	${NORMAL_LINT}

ata-cyrix.o: $S/dev/ata/chipsets/ata-cyrix.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-highpoint.ln: $S/dev/ata/chipsets/ata-highpoint.c
	${NORMAL_LINT}

ata-highpoint.o: $S/dev/ata/chipsets/ata-highpoint.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-intel.ln: $S/dev/ata/chipsets/ata-intel.c
	${NORMAL_LINT}

ata-intel.o: $S/dev/ata/chipsets/ata-intel.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-ite.ln: $S/dev/ata/chipsets/ata-ite.c
	${NORMAL_LINT}

ata-ite.o: $S/dev/ata/chipsets/ata-ite.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-jmicron.ln: $S/dev/ata/chipsets/ata-jmicron.c
	${NORMAL_LINT}

ata-jmicron.o: $S/dev/ata/chipsets/ata-jmicron.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-marvell.ln: $S/dev/ata/chipsets/ata-marvell.c
	${NORMAL_LINT}

ata-marvell.o: $S/dev/ata/chipsets/ata-marvell.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-micron.ln: $S/dev/ata/chipsets/ata-micron.c
	${NORMAL_LINT}

ata-micron.o: $S/dev/ata/chipsets/ata-micron.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-national.ln: $S/dev/ata/chipsets/ata-national.c
	${NORMAL_LINT}

ata-national.o: $S/dev/ata/chipsets/ata-national.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-netcell.ln: $S/dev/ata/chipsets/ata-netcell.c
	${NORMAL_LINT}

ata-netcell.o: $S/dev/ata/chipsets/ata-netcell.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-nvidia.ln: $S/dev/ata/chipsets/ata-nvidia.c
	${NORMAL_LINT}

ata-nvidia.o: $S/dev/ata/chipsets/ata-nvidia.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-promise.ln: $S/dev/ata/chipsets/ata-promise.c
	${NORMAL_LINT}

ata-promise.o: $S/dev/ata/chipsets/ata-promise.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-serverworks.ln: $S/dev/ata/chipsets/ata-serverworks.c
	${NORMAL_LINT}

ata-serverworks.o: $S/dev/ata/chipsets/ata-serverworks.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-siliconimage.ln: $S/dev/ata/chipsets/ata-siliconimage.c
	${NORMAL_LINT}

ata-siliconimage.o: $S/dev/ata/chipsets/ata-siliconimage.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-sis.ln: $S/dev/ata/chipsets/ata-sis.c
	${NORMAL_LINT}

ata-sis.o: $S/dev/ata/chipsets/ata-sis.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-via.ln: $S/dev/ata/chipsets/ata-via.c
	${NORMAL_LINT}

ata-via.o: $S/dev/ata/chipsets/ata-via.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-disk.ln: $S/dev/ata/ata-disk.c
	${NORMAL_LINT}

ata-disk.o: $S/dev/ata/ata-disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ata-raid.ln: $S/dev/ata/ata-raid.c
	${NORMAL_LINT}

ata-raid.o: $S/dev/ata/ata-raid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atapi-cd.ln: $S/dev/ata/atapi-cd.c
	${NORMAL_LINT}

atapi-cd.o: $S/dev/ata/atapi-cd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atapi-fd.ln: $S/dev/ata/atapi-fd.c
	${NORMAL_LINT}

atapi-fd.o: $S/dev/ata/atapi-fd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atapi-tape.ln: $S/dev/ata/atapi-tape.c
	${NORMAL_LINT}

atapi-tape.o: $S/dev/ata/atapi-tape.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ath.ln: $S/dev/ath/if_ath.c
	${NORMAL_LINT}

if_ath.o: $S/dev/ath/if_ath.c
	${NORMAL_C} -I$S/dev/ath

if_ath_pci.ln: $S/dev/ath/if_ath_pci.c
	${NORMAL_LINT}

if_ath_pci.o: $S/dev/ath/if_ath_pci.c
	${NORMAL_C} -I$S/dev/ath

ah_osdep.ln: $S/dev/ath/ah_osdep.c
	${NORMAL_LINT}

ah_osdep.o: $S/dev/ath/ah_osdep.c
	${NORMAL_C} -I$S/dev/ath

ah.ln: $S/dev/ath/ath_hal/ah.c
	${NORMAL_LINT}

ah.o: $S/dev/ath/ath_hal/ah.c
	${NORMAL_C} -I$S/dev/ath

ah_eeprom_v1.ln: $S/dev/ath/ath_hal/ah_eeprom_v1.c
	${NORMAL_LINT}

ah_eeprom_v1.o: $S/dev/ath/ath_hal/ah_eeprom_v1.c
	${NORMAL_C} -I$S/dev/ath

ah_eeprom_v3.ln: $S/dev/ath/ath_hal/ah_eeprom_v3.c
	${NORMAL_LINT}

ah_eeprom_v3.o: $S/dev/ath/ath_hal/ah_eeprom_v3.c
	${NORMAL_C} -I$S/dev/ath

ah_eeprom_v14.ln: $S/dev/ath/ath_hal/ah_eeprom_v14.c
	${NORMAL_LINT}

ah_eeprom_v14.o: $S/dev/ath/ath_hal/ah_eeprom_v14.c
	${NORMAL_C} -I$S/dev/ath

ah_regdomain.ln: $S/dev/ath/ath_hal/ah_regdomain.c
	${NORMAL_LINT}

ah_regdomain.o: $S/dev/ath/ath_hal/ah_regdomain.c
	${NORMAL_C} -I$S/dev/ath

ar5210_attach.ln: $S/dev/ath/ath_hal/ar5210/ar5210_attach.c
	${NORMAL_LINT}

ar5210_attach.o: $S/dev/ath/ath_hal/ar5210/ar5210_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_beacon.ln: $S/dev/ath/ath_hal/ar5210/ar5210_beacon.c
	${NORMAL_LINT}

ar5210_beacon.o: $S/dev/ath/ath_hal/ar5210/ar5210_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_interrupts.ln: $S/dev/ath/ath_hal/ar5210/ar5210_interrupts.c
	${NORMAL_LINT}

ar5210_interrupts.o: $S/dev/ath/ath_hal/ar5210/ar5210_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_keycache.ln: $S/dev/ath/ath_hal/ar5210/ar5210_keycache.c
	${NORMAL_LINT}

ar5210_keycache.o: $S/dev/ath/ath_hal/ar5210/ar5210_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_misc.ln: $S/dev/ath/ath_hal/ar5210/ar5210_misc.c
	${NORMAL_LINT}

ar5210_misc.o: $S/dev/ath/ath_hal/ar5210/ar5210_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_phy.ln: $S/dev/ath/ath_hal/ar5210/ar5210_phy.c
	${NORMAL_LINT}

ar5210_phy.o: $S/dev/ath/ath_hal/ar5210/ar5210_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_power.ln: $S/dev/ath/ath_hal/ar5210/ar5210_power.c
	${NORMAL_LINT}

ar5210_power.o: $S/dev/ath/ath_hal/ar5210/ar5210_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_recv.ln: $S/dev/ath/ath_hal/ar5210/ar5210_recv.c
	${NORMAL_LINT}

ar5210_recv.o: $S/dev/ath/ath_hal/ar5210/ar5210_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_reset.ln: $S/dev/ath/ath_hal/ar5210/ar5210_reset.c
	${NORMAL_LINT}

ar5210_reset.o: $S/dev/ath/ath_hal/ar5210/ar5210_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5210_xmit.ln: $S/dev/ath/ath_hal/ar5210/ar5210_xmit.c
	${NORMAL_LINT}

ar5210_xmit.o: $S/dev/ath/ath_hal/ar5210/ar5210_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_attach.ln: $S/dev/ath/ath_hal/ar5211/ar5211_attach.c
	${NORMAL_LINT}

ar5211_attach.o: $S/dev/ath/ath_hal/ar5211/ar5211_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_beacon.ln: $S/dev/ath/ath_hal/ar5211/ar5211_beacon.c
	${NORMAL_LINT}

ar5211_beacon.o: $S/dev/ath/ath_hal/ar5211/ar5211_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_interrupts.ln: $S/dev/ath/ath_hal/ar5211/ar5211_interrupts.c
	${NORMAL_LINT}

ar5211_interrupts.o: $S/dev/ath/ath_hal/ar5211/ar5211_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_keycache.ln: $S/dev/ath/ath_hal/ar5211/ar5211_keycache.c
	${NORMAL_LINT}

ar5211_keycache.o: $S/dev/ath/ath_hal/ar5211/ar5211_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_misc.ln: $S/dev/ath/ath_hal/ar5211/ar5211_misc.c
	${NORMAL_LINT}

ar5211_misc.o: $S/dev/ath/ath_hal/ar5211/ar5211_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_phy.ln: $S/dev/ath/ath_hal/ar5211/ar5211_phy.c
	${NORMAL_LINT}

ar5211_phy.o: $S/dev/ath/ath_hal/ar5211/ar5211_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_power.ln: $S/dev/ath/ath_hal/ar5211/ar5211_power.c
	${NORMAL_LINT}

ar5211_power.o: $S/dev/ath/ath_hal/ar5211/ar5211_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_recv.ln: $S/dev/ath/ath_hal/ar5211/ar5211_recv.c
	${NORMAL_LINT}

ar5211_recv.o: $S/dev/ath/ath_hal/ar5211/ar5211_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_reset.ln: $S/dev/ath/ath_hal/ar5211/ar5211_reset.c
	${NORMAL_LINT}

ar5211_reset.o: $S/dev/ath/ath_hal/ar5211/ar5211_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5211_xmit.ln: $S/dev/ath/ath_hal/ar5211/ar5211_xmit.c
	${NORMAL_LINT}

ar5211_xmit.o: $S/dev/ath/ath_hal/ar5211/ar5211_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_ani.ln: $S/dev/ath/ath_hal/ar5212/ar5212_ani.c
	${NORMAL_LINT}

ar5212_ani.o: $S/dev/ath/ath_hal/ar5212/ar5212_ani.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_attach.ln: $S/dev/ath/ath_hal/ar5212/ar5212_attach.c
	${NORMAL_LINT}

ar5212_attach.o: $S/dev/ath/ath_hal/ar5212/ar5212_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_beacon.ln: $S/dev/ath/ath_hal/ar5212/ar5212_beacon.c
	${NORMAL_LINT}

ar5212_beacon.o: $S/dev/ath/ath_hal/ar5212/ar5212_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_eeprom.ln: $S/dev/ath/ath_hal/ar5212/ar5212_eeprom.c
	${NORMAL_LINT}

ar5212_eeprom.o: $S/dev/ath/ath_hal/ar5212/ar5212_eeprom.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_gpio.ln: $S/dev/ath/ath_hal/ar5212/ar5212_gpio.c
	${NORMAL_LINT}

ar5212_gpio.o: $S/dev/ath/ath_hal/ar5212/ar5212_gpio.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_interrupts.ln: $S/dev/ath/ath_hal/ar5212/ar5212_interrupts.c
	${NORMAL_LINT}

ar5212_interrupts.o: $S/dev/ath/ath_hal/ar5212/ar5212_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_keycache.ln: $S/dev/ath/ath_hal/ar5212/ar5212_keycache.c
	${NORMAL_LINT}

ar5212_keycache.o: $S/dev/ath/ath_hal/ar5212/ar5212_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_misc.ln: $S/dev/ath/ath_hal/ar5212/ar5212_misc.c
	${NORMAL_LINT}

ar5212_misc.o: $S/dev/ath/ath_hal/ar5212/ar5212_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_phy.ln: $S/dev/ath/ath_hal/ar5212/ar5212_phy.c
	${NORMAL_LINT}

ar5212_phy.o: $S/dev/ath/ath_hal/ar5212/ar5212_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_power.ln: $S/dev/ath/ath_hal/ar5212/ar5212_power.c
	${NORMAL_LINT}

ar5212_power.o: $S/dev/ath/ath_hal/ar5212/ar5212_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_recv.ln: $S/dev/ath/ath_hal/ar5212/ar5212_recv.c
	${NORMAL_LINT}

ar5212_recv.o: $S/dev/ath/ath_hal/ar5212/ar5212_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_reset.ln: $S/dev/ath/ath_hal/ar5212/ar5212_reset.c
	${NORMAL_LINT}

ar5212_reset.o: $S/dev/ath/ath_hal/ar5212/ar5212_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_rfgain.ln: $S/dev/ath/ath_hal/ar5212/ar5212_rfgain.c
	${NORMAL_LINT}

ar5212_rfgain.o: $S/dev/ath/ath_hal/ar5212/ar5212_rfgain.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5212_xmit.ln: $S/dev/ath/ath_hal/ar5212/ar5212_xmit.c
	${NORMAL_LINT}

ar5212_xmit.o: $S/dev/ath/ath_hal/ar5212/ar5212_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_ani.ln: $S/dev/ath/ath_hal/ar5416/ar5416_ani.c
	${NORMAL_LINT}

ar5416_ani.o: $S/dev/ath/ath_hal/ar5416/ar5416_ani.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_attach.ln: $S/dev/ath/ath_hal/ar5416/ar5416_attach.c
	${NORMAL_LINT}

ar5416_attach.o: $S/dev/ath/ath_hal/ar5416/ar5416_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_beacon.ln: $S/dev/ath/ath_hal/ar5416/ar5416_beacon.c
	${NORMAL_LINT}

ar5416_beacon.o: $S/dev/ath/ath_hal/ar5416/ar5416_beacon.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_cal.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal.c
	${NORMAL_LINT}

ar5416_cal.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_cal_iq.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal_iq.c
	${NORMAL_LINT}

ar5416_cal_iq.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal_iq.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_cal_adcgain.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcgain.c
	${NORMAL_LINT}

ar5416_cal_adcgain.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcgain.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_cal_adcdc.ln: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcdc.c
	${NORMAL_LINT}

ar5416_cal_adcdc.o: $S/dev/ath/ath_hal/ar5416/ar5416_cal_adcdc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_eeprom.ln: $S/dev/ath/ath_hal/ar5416/ar5416_eeprom.c
	${NORMAL_LINT}

ar5416_eeprom.o: $S/dev/ath/ath_hal/ar5416/ar5416_eeprom.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_gpio.ln: $S/dev/ath/ath_hal/ar5416/ar5416_gpio.c
	${NORMAL_LINT}

ar5416_gpio.o: $S/dev/ath/ath_hal/ar5416/ar5416_gpio.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_interrupts.ln: $S/dev/ath/ath_hal/ar5416/ar5416_interrupts.c
	${NORMAL_LINT}

ar5416_interrupts.o: $S/dev/ath/ath_hal/ar5416/ar5416_interrupts.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_keycache.ln: $S/dev/ath/ath_hal/ar5416/ar5416_keycache.c
	${NORMAL_LINT}

ar5416_keycache.o: $S/dev/ath/ath_hal/ar5416/ar5416_keycache.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_misc.ln: $S/dev/ath/ath_hal/ar5416/ar5416_misc.c
	${NORMAL_LINT}

ar5416_misc.o: $S/dev/ath/ath_hal/ar5416/ar5416_misc.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_phy.ln: $S/dev/ath/ath_hal/ar5416/ar5416_phy.c
	${NORMAL_LINT}

ar5416_phy.o: $S/dev/ath/ath_hal/ar5416/ar5416_phy.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_power.ln: $S/dev/ath/ath_hal/ar5416/ar5416_power.c
	${NORMAL_LINT}

ar5416_power.o: $S/dev/ath/ath_hal/ar5416/ar5416_power.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_recv.ln: $S/dev/ath/ath_hal/ar5416/ar5416_recv.c
	${NORMAL_LINT}

ar5416_recv.o: $S/dev/ath/ath_hal/ar5416/ar5416_recv.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_reset.ln: $S/dev/ath/ath_hal/ar5416/ar5416_reset.c
	${NORMAL_LINT}

ar5416_reset.o: $S/dev/ath/ath_hal/ar5416/ar5416_reset.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5416_xmit.ln: $S/dev/ath/ath_hal/ar5416/ar5416_xmit.c
	${NORMAL_LINT}

ar5416_xmit.o: $S/dev/ath/ath_hal/ar5416/ar5416_xmit.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar9160_attach.ln: $S/dev/ath/ath_hal/ar5416/ar9160_attach.c
	${NORMAL_LINT}

ar9160_attach.o: $S/dev/ath/ath_hal/ar5416/ar9160_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar9280_attach.ln: $S/dev/ath/ath_hal/ar5416/ar9280_attach.c
	${NORMAL_LINT}

ar9280_attach.o: $S/dev/ath/ath_hal/ar5416/ar9280_attach.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar2413.ln: $S/dev/ath/ath_hal/ar5212/ar2413.c
	${NORMAL_LINT}

ar2413.o: $S/dev/ath/ath_hal/ar5212/ar2413.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar2425.ln: $S/dev/ath/ath_hal/ar5212/ar2425.c
	${NORMAL_LINT}

ar2425.o: $S/dev/ath/ath_hal/ar5212/ar2425.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5111.ln: $S/dev/ath/ath_hal/ar5212/ar5111.c
	${NORMAL_LINT}

ar5111.o: $S/dev/ath/ath_hal/ar5212/ar5111.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5112.ln: $S/dev/ath/ath_hal/ar5212/ar5112.c
	${NORMAL_LINT}

ar5112.o: $S/dev/ath/ath_hal/ar5212/ar5112.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar5413.ln: $S/dev/ath/ath_hal/ar5212/ar5413.c
	${NORMAL_LINT}

ar5413.o: $S/dev/ath/ath_hal/ar5212/ar5413.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar2133.ln: $S/dev/ath/ath_hal/ar5416/ar2133.c
	${NORMAL_LINT}

ar2133.o: $S/dev/ath/ath_hal/ar5416/ar2133.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

ar9280.ln: $S/dev/ath/ath_hal/ar5416/ar9280.c
	${NORMAL_LINT}

ar9280.o: $S/dev/ath/ath_hal/ar5416/ar9280.c
	${NORMAL_C} -I$S/dev/ath -I$S/dev/ath/ath_hal

sample.ln: $S/dev/ath/ath_rate/sample/sample.c
	${NORMAL_LINT}

sample.o: $S/dev/ath/ath_rate/sample/sample.c
	${NORMAL_C} -I$S/dev/ath

if_bce.ln: $S/dev/bce/if_bce.c
	${NORMAL_LINT}

if_bce.o: $S/dev/bce/if_bce.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_bfe.ln: $S/dev/bfe/if_bfe.c
	${NORMAL_LINT}

if_bfe.o: $S/dev/bfe/if_bfe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_bge.ln: $S/dev/bge/if_bge.c
	${NORMAL_LINT}

if_bge.o: $S/dev/bge/if_bge.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bt.ln: $S/dev/buslogic/bt.c
	${NORMAL_LINT}

bt.o: $S/dev/buslogic/bt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bt_eisa.ln: $S/dev/buslogic/bt_eisa.c
	${NORMAL_LINT}

bt_eisa.o: $S/dev/buslogic/bt_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bt_isa.ln: $S/dev/buslogic/bt_isa.c
	${NORMAL_LINT}

bt_isa.o: $S/dev/buslogic/bt_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bt_pci.ln: $S/dev/buslogic/bt_pci.c
	${NORMAL_LINT}

bt_pci.o: $S/dev/buslogic/bt_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cardbus.ln: $S/dev/cardbus/cardbus.c
	${NORMAL_LINT}

cardbus.o: $S/dev/cardbus/cardbus.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cardbus_cis.ln: $S/dev/cardbus/cardbus_cis.c
	${NORMAL_LINT}

cardbus_cis.o: $S/dev/cardbus/cardbus_cis.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cardbus_device.ln: $S/dev/cardbus/cardbus_device.c
	${NORMAL_LINT}

cardbus_device.o: $S/dev/cardbus/cardbus_device.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ciss.ln: $S/dev/ciss/ciss.c
	${NORMAL_LINT}

ciss.o: $S/dev/ciss/ciss.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ichss.ln: $S/dev/cpufreq/ichss.c
	${NORMAL_LINT}

ichss.o: $S/dev/cpufreq/ichss.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_cs.ln: $S/dev/cs/if_cs.c
	${NORMAL_LINT}

if_cs.o: $S/dev/cs/if_cs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_cs_isa.ln: $S/dev/cs/if_cs_isa.c
	${NORMAL_LINT}

if_cs_isa.o: $S/dev/cs/if_cs_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_cs_pccard.ln: $S/dev/cs/if_cs_pccard.c
	${NORMAL_LINT}

if_cs_pccard.o: $S/dev/cs/if_cs_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_dc.ln: $S/dev/dc/if_dc.c
	${NORMAL_LINT}

if_dc.o: $S/dev/dc/if_dc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dcphy.ln: $S/dev/dc/dcphy.c
	${NORMAL_LINT}

dcphy.o: $S/dev/dc/dcphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pnphy.ln: $S/dev/dc/pnphy.c
	${NORMAL_LINT}

pnphy.o: $S/dev/dc/pnphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dcons.ln: $S/dev/dcons/dcons.c
	${NORMAL_LINT}

dcons.o: $S/dev/dcons/dcons.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dcons_crom.ln: $S/dev/dcons/dcons_crom.c
	${NORMAL_LINT}

dcons_crom.o: $S/dev/dcons/dcons_crom.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dcons_os.ln: $S/dev/dcons/dcons_os.c
	${NORMAL_LINT}

dcons_os.o: $S/dev/dcons/dcons_os.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_de.ln: $S/dev/de/if_de.c
	${NORMAL_LINT}

if_de.o: $S/dev/de/if_de.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dpt_eisa.ln: $S/dev/dpt/dpt_eisa.c
	${NORMAL_LINT}

dpt_eisa.o: $S/dev/dpt/dpt_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dpt_pci.ln: $S/dev/dpt/dpt_pci.c
	${NORMAL_LINT}

dpt_pci.o: $S/dev/dpt/dpt_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dpt_scsi.ln: $S/dev/dpt/dpt_scsi.c
	${NORMAL_LINT}

dpt_scsi.o: $S/dev/dpt/dpt_scsi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed.ln: $S/dev/ed/if_ed.c
	${NORMAL_LINT}

if_ed.o: $S/dev/ed/if_ed.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed_novell.ln: $S/dev/ed/if_ed_novell.c
	${NORMAL_LINT}

if_ed_novell.o: $S/dev/ed/if_ed_novell.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed_rtl80x9.ln: $S/dev/ed/if_ed_rtl80x9.c
	${NORMAL_LINT}

if_ed_rtl80x9.o: $S/dev/ed/if_ed_rtl80x9.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed_pccard.ln: $S/dev/ed/if_ed_pccard.c
	${NORMAL_LINT}

if_ed_pccard.o: $S/dev/ed/if_ed_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed_pci.ln: $S/dev/ed/if_ed_pci.c
	${NORMAL_LINT}

if_ed_pci.o: $S/dev/ed/if_ed_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

eisa_if.ln: $S/dev/eisa/eisa_if.m
	${NORMAL_LINT}

eisa_if.o: $S/dev/eisa/eisa_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

eisaconf.ln: $S/dev/eisa/eisaconf.c
	${NORMAL_LINT}

eisaconf.o: $S/dev/eisa/eisaconf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_em.ln: $S/dev/e1000/if_em.c
	${NORMAL_LINT}

if_em.o: $S/dev/e1000/if_em.c
	${NORMAL_C} -I$S/dev/e1000

if_igb.ln: $S/dev/e1000/if_igb.c
	${NORMAL_LINT}

if_igb.o: $S/dev/e1000/if_igb.c
	${NORMAL_C} -I$S/dev/e1000

e1000_80003es2lan.ln: $S/dev/e1000/e1000_80003es2lan.c
	${NORMAL_LINT}

e1000_80003es2lan.o: $S/dev/e1000/e1000_80003es2lan.c
	${NORMAL_C} -I$S/dev/e1000

e1000_82540.ln: $S/dev/e1000/e1000_82540.c
	${NORMAL_LINT}

e1000_82540.o: $S/dev/e1000/e1000_82540.c
	${NORMAL_C} -I$S/dev/e1000

e1000_82541.ln: $S/dev/e1000/e1000_82541.c
	${NORMAL_LINT}

e1000_82541.o: $S/dev/e1000/e1000_82541.c
	${NORMAL_C} -I$S/dev/e1000

e1000_82542.ln: $S/dev/e1000/e1000_82542.c
	${NORMAL_LINT}

e1000_82542.o: $S/dev/e1000/e1000_82542.c
	${NORMAL_C} -I$S/dev/e1000

e1000_82543.ln: $S/dev/e1000/e1000_82543.c
	${NORMAL_LINT}

e1000_82543.o: $S/dev/e1000/e1000_82543.c
	${NORMAL_C} -I$S/dev/e1000

e1000_82571.ln: $S/dev/e1000/e1000_82571.c
	${NORMAL_LINT}

e1000_82571.o: $S/dev/e1000/e1000_82571.c
	${NORMAL_C} -I$S/dev/e1000

e1000_82575.ln: $S/dev/e1000/e1000_82575.c
	${NORMAL_LINT}

e1000_82575.o: $S/dev/e1000/e1000_82575.c
	${NORMAL_C} -I$S/dev/igb

e1000_ich8lan.ln: $S/dev/e1000/e1000_ich8lan.c
	${NORMAL_LINT}

e1000_ich8lan.o: $S/dev/e1000/e1000_ich8lan.c
	${NORMAL_C} -I$S/dev/e1000

e1000_api.ln: $S/dev/e1000/e1000_api.c
	${NORMAL_LINT}

e1000_api.o: $S/dev/e1000/e1000_api.c
	${NORMAL_C} -I$S/dev/e1000

e1000_mac.ln: $S/dev/e1000/e1000_mac.c
	${NORMAL_LINT}

e1000_mac.o: $S/dev/e1000/e1000_mac.c
	${NORMAL_C} -I$S/dev/e1000

e1000_manage.ln: $S/dev/e1000/e1000_manage.c
	${NORMAL_LINT}

e1000_manage.o: $S/dev/e1000/e1000_manage.c
	${NORMAL_C} -I$S/dev/e1000

e1000_nvm.ln: $S/dev/e1000/e1000_nvm.c
	${NORMAL_LINT}

e1000_nvm.o: $S/dev/e1000/e1000_nvm.c
	${NORMAL_C} -I$S/dev/e1000

e1000_phy.ln: $S/dev/e1000/e1000_phy.c
	${NORMAL_LINT}

e1000_phy.o: $S/dev/e1000/e1000_phy.c
	${NORMAL_C} -I$S/dev/e1000

e1000_osdep.ln: $S/dev/e1000/e1000_osdep.c
	${NORMAL_LINT}

e1000_osdep.o: $S/dev/e1000/e1000_osdep.c
	${NORMAL_C} -I$S/dev/e1000

if_et.ln: $S/dev/et/if_et.c
	${NORMAL_LINT}

if_et.o: $S/dev/et/if_et.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ep.ln: $S/dev/ep/if_ep.c
	${NORMAL_LINT}

if_ep.o: $S/dev/ep/if_ep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ep_eisa.ln: $S/dev/ep/if_ep_eisa.c
	${NORMAL_LINT}

if_ep_eisa.o: $S/dev/ep/if_ep_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ep_isa.ln: $S/dev/ep/if_ep_isa.c
	${NORMAL_LINT}

if_ep_isa.o: $S/dev/ep/if_ep_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ep_pccard.ln: $S/dev/ep/if_ep_pccard.c
	${NORMAL_LINT}

if_ep_pccard.o: $S/dev/ep/if_ep_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ex.ln: $S/dev/ex/if_ex.c
	${NORMAL_LINT}

if_ex.o: $S/dev/ex/if_ex.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ex_isa.ln: $S/dev/ex/if_ex_isa.c
	${NORMAL_LINT}

if_ex_isa.o: $S/dev/ex/if_ex_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ex_pccard.ln: $S/dev/ex/if_ex_pccard.c
	${NORMAL_LINT}

if_ex_pccard.o: $S/dev/ex/if_ex_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exca.ln: $S/dev/exca/exca.c
	${NORMAL_LINT}

exca.o: $S/dev/exca/exca.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

splash.ln: $S/dev/fb/splash.c
	${NORMAL_LINT}

splash.o: $S/dev/fb/splash.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fe.ln: $S/dev/fe/if_fe.c
	${NORMAL_LINT}

if_fe.o: $S/dev/fe/if_fe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fe_pccard.ln: $S/dev/fe/if_fe_pccard.c
	${NORMAL_LINT}

if_fe_pccard.o: $S/dev/fe/if_fe_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

firewire.ln: $S/dev/firewire/firewire.c
	${NORMAL_LINT}

firewire.o: $S/dev/firewire/firewire.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fwcrom.ln: $S/dev/firewire/fwcrom.c
	${NORMAL_LINT}

fwcrom.o: $S/dev/firewire/fwcrom.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fwdev.ln: $S/dev/firewire/fwdev.c
	${NORMAL_LINT}

fwdev.o: $S/dev/firewire/fwdev.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fwdma.ln: $S/dev/firewire/fwdma.c
	${NORMAL_LINT}

fwdma.o: $S/dev/firewire/fwdma.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fwmem.ln: $S/dev/firewire/fwmem.c
	${NORMAL_LINT}

fwmem.o: $S/dev/firewire/fwmem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fwohci.ln: $S/dev/firewire/fwohci.c
	${NORMAL_LINT}

fwohci.o: $S/dev/firewire/fwohci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fwohci_pci.ln: $S/dev/firewire/fwohci_pci.c
	${NORMAL_LINT}

fwohci_pci.o: $S/dev/firewire/fwohci_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fwe.ln: $S/dev/firewire/if_fwe.c
	${NORMAL_LINT}

if_fwe.o: $S/dev/firewire/if_fwe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fwip.ln: $S/dev/firewire/if_fwip.c
	${NORMAL_LINT}

if_fwip.o: $S/dev/firewire/if_fwip.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fxp.ln: $S/dev/fxp/if_fxp.c
	${NORMAL_LINT}

if_fxp.o: $S/dev/fxp/if_fxp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hptiop.ln: $S/dev/hptiop/hptiop.c
	${NORMAL_LINT}

hptiop.o: $S/dev/hptiop/hptiop.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ida.ln: $S/dev/ida/ida.c
	${NORMAL_LINT}

ida.o: $S/dev/ida/ida.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ida_disk.ln: $S/dev/ida/ida_disk.c
	${NORMAL_LINT}

ida_disk.o: $S/dev/ida/ida_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ida_eisa.ln: $S/dev/ida/ida_eisa.c
	${NORMAL_LINT}

ida_eisa.o: $S/dev/ida/ida_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ida_pci.ln: $S/dev/ida/ida_pci.c
	${NORMAL_LINT}

ida_pci.o: $S/dev/ida/ida_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ie.ln: $S/dev/ie/if_ie.c
	${NORMAL_LINT}

if_ie.o: $S/dev/ie/if_ie.c
	${NORMAL_C_NOWERROR}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ie_isa.ln: $S/dev/ie/if_ie_isa.c
	${NORMAL_LINT}

if_ie_isa.o: $S/dev/ie/if_ie_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

iir.ln: $S/dev/iir/iir.c
	${NORMAL_LINT}

iir.o: $S/dev/iir/iir.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

iir_ctrl.ln: $S/dev/iir/iir_ctrl.c
	${NORMAL_LINT}

iir_ctrl.o: $S/dev/iir/iir_ctrl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

iir_pci.ln: $S/dev/iir/iir_pci.c
	${NORMAL_LINT}

iir_pci.o: $S/dev/iir/iir_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ips.ln: $S/dev/ips/ips.c
	${NORMAL_LINT}

ips.o: $S/dev/ips/ips.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ips_commands.ln: $S/dev/ips/ips_commands.c
	${NORMAL_LINT}

ips_commands.o: $S/dev/ips/ips_commands.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ips_disk.ln: $S/dev/ips/ips_disk.c
	${NORMAL_LINT}

ips_disk.o: $S/dev/ips/ips_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ips_ioctl.ln: $S/dev/ips/ips_ioctl.c
	${NORMAL_LINT}

ips_ioctl.o: $S/dev/ips/ips_ioctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ips_pci.ln: $S/dev/ips/ips_pci.c
	${NORMAL_LINT}

ips_pci.o: $S/dev/ips/ips_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isp.ln: $S/dev/isp/isp.c
	${NORMAL_LINT}

isp.o: $S/dev/isp/isp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isp_freebsd.ln: $S/dev/isp/isp_freebsd.c
	${NORMAL_LINT}

isp_freebsd.o: $S/dev/isp/isp_freebsd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isp_library.ln: $S/dev/isp/isp_library.c
	${NORMAL_LINT}

isp_library.o: $S/dev/isp/isp_library.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isp_pci.ln: $S/dev/isp/isp_pci.c
	${NORMAL_LINT}

isp_pci.o: $S/dev/isp/isp_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isp_target.ln: $S/dev/isp/isp_target.c
	${NORMAL_LINT}

isp_target.o: $S/dev/isp/isp_target.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ixgb.ln: $S/dev/ixgb/if_ixgb.c
	${NORMAL_LINT}

if_ixgb.o: $S/dev/ixgb/if_ixgb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ixgb_ee.ln: $S/dev/ixgb/ixgb_ee.c
	${NORMAL_LINT}

ixgb_ee.o: $S/dev/ixgb/ixgb_ee.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ixgb_hw.ln: $S/dev/ixgb/ixgb_hw.c
	${NORMAL_LINT}

ixgb_hw.o: $S/dev/ixgb/ixgb_hw.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_jme.ln: $S/dev/jme/if_jme.c
	${NORMAL_LINT}

if_jme.o: $S/dev/jme/if_jme.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kbdmux.ln: $S/dev/kbdmux/kbdmux.c
	${NORMAL_LINT}

kbdmux.o: $S/dev/kbdmux/kbdmux.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

am7990.ln: $S/dev/le/am7990.c
	${NORMAL_LINT}

am7990.o: $S/dev/le/am7990.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

am79900.ln: $S/dev/le/am79900.c
	${NORMAL_LINT}

am79900.o: $S/dev/le/am79900.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_le_pci.ln: $S/dev/le/if_le_pci.c
	${NORMAL_LINT}

if_le_pci.o: $S/dev/le/if_le_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

lance.ln: $S/dev/le/lance.c
	${NORMAL_LINT}

lance.o: $S/dev/le/lance.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

led.ln: $S/dev/led/led.c
	${NORMAL_LINT}

led.o: $S/dev/led/led.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_lge.ln: $S/dev/lge/if_lge.c
	${NORMAL_LINT}

if_lge.o: $S/dev/lge/if_lge.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

md.ln: $S/dev/md/md.c
	${NORMAL_LINT}

md.o: $S/dev/md/md.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

memdev.ln: $S/dev/mem/memdev.c
	${NORMAL_LINT}

memdev.o: $S/dev/mem/memdev.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mfi.ln: $S/dev/mfi/mfi.c
	${NORMAL_LINT}

mfi.o: $S/dev/mfi/mfi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mfi_debug.ln: $S/dev/mfi/mfi_debug.c
	${NORMAL_LINT}

mfi_debug.o: $S/dev/mfi/mfi_debug.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mfi_pci.ln: $S/dev/mfi/mfi_pci.c
	${NORMAL_LINT}

mfi_pci.o: $S/dev/mfi/mfi_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mfi_disk.ln: $S/dev/mfi/mfi_disk.c
	${NORMAL_LINT}

mfi_disk.o: $S/dev/mfi/mfi_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acphy.ln: $S/dev/mii/acphy.c
	${NORMAL_LINT}

acphy.o: $S/dev/mii/acphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

amphy.ln: $S/dev/mii/amphy.c
	${NORMAL_LINT}

amphy.o: $S/dev/mii/amphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atphy.ln: $S/dev/mii/atphy.c
	${NORMAL_LINT}

atphy.o: $S/dev/mii/atphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

axphy.ln: $S/dev/mii/axphy.c
	${NORMAL_LINT}

axphy.o: $S/dev/mii/axphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bmtphy.ln: $S/dev/mii/bmtphy.c
	${NORMAL_LINT}

bmtphy.o: $S/dev/mii/bmtphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

brgphy.ln: $S/dev/mii/brgphy.c
	${NORMAL_LINT}

brgphy.o: $S/dev/mii/brgphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ciphy.ln: $S/dev/mii/ciphy.c
	${NORMAL_LINT}

ciphy.o: $S/dev/mii/ciphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

e1000phy.ln: $S/dev/mii/e1000phy.c
	${NORMAL_LINT}

e1000phy.o: $S/dev/mii/e1000phy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exphy.ln: $S/dev/mii/exphy.c
	${NORMAL_LINT}

exphy.o: $S/dev/mii/exphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

gentbi.ln: $S/dev/mii/gentbi.c
	${NORMAL_LINT}

gentbi.o: $S/dev/mii/gentbi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

icsphy.ln: $S/dev/mii/icsphy.c
	${NORMAL_LINT}

icsphy.o: $S/dev/mii/icsphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

inphy.ln: $S/dev/mii/inphy.c
	${NORMAL_LINT}

inphy.o: $S/dev/mii/inphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip1000phy.ln: $S/dev/mii/ip1000phy.c
	${NORMAL_LINT}

ip1000phy.o: $S/dev/mii/ip1000phy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

jmphy.ln: $S/dev/mii/jmphy.c
	${NORMAL_LINT}

jmphy.o: $S/dev/mii/jmphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

lxtphy.ln: $S/dev/mii/lxtphy.c
	${NORMAL_LINT}

lxtphy.o: $S/dev/mii/lxtphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mii.ln: $S/dev/mii/mii.c
	${NORMAL_LINT}

mii.o: $S/dev/mii/mii.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mii_physubr.ln: $S/dev/mii/mii_physubr.c
	${NORMAL_LINT}

mii_physubr.o: $S/dev/mii/mii_physubr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

miibus_if.ln: $S/dev/mii/miibus_if.m
	${NORMAL_LINT}

miibus_if.o: $S/dev/mii/miibus_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mlphy.ln: $S/dev/mii/mlphy.c
	${NORMAL_LINT}

mlphy.o: $S/dev/mii/mlphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsgphy.ln: $S/dev/mii/nsgphy.c
	${NORMAL_LINT}

nsgphy.o: $S/dev/mii/nsgphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsphy.ln: $S/dev/mii/nsphy.c
	${NORMAL_LINT}

nsphy.o: $S/dev/mii/nsphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsphyter.ln: $S/dev/mii/nsphyter.c
	${NORMAL_LINT}

nsphyter.o: $S/dev/mii/nsphyter.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pnaphy.ln: $S/dev/mii/pnaphy.c
	${NORMAL_LINT}

pnaphy.o: $S/dev/mii/pnaphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

qsphy.ln: $S/dev/mii/qsphy.c
	${NORMAL_LINT}

qsphy.o: $S/dev/mii/qsphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rgephy.ln: $S/dev/mii/rgephy.c
	${NORMAL_LINT}

rgephy.o: $S/dev/mii/rgephy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rlphy.ln: $S/dev/mii/rlphy.c
	${NORMAL_LINT}

rlphy.o: $S/dev/mii/rlphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ruephy.ln: $S/dev/mii/ruephy.c
	${NORMAL_LINT}

ruephy.o: $S/dev/mii/ruephy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

smcphy.ln: $S/dev/mii/smcphy.c
	${NORMAL_LINT}

smcphy.o: $S/dev/mii/smcphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tdkphy.ln: $S/dev/mii/tdkphy.c
	${NORMAL_LINT}

tdkphy.o: $S/dev/mii/tdkphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tlphy.ln: $S/dev/mii/tlphy.c
	${NORMAL_LINT}

tlphy.o: $S/dev/mii/tlphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

truephy.ln: $S/dev/mii/truephy.c
	${NORMAL_LINT}

truephy.o: $S/dev/mii/truephy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ukphy.ln: $S/dev/mii/ukphy.c
	${NORMAL_LINT}

ukphy.o: $S/dev/mii/ukphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ukphy_subr.ln: $S/dev/mii/ukphy_subr.c
	${NORMAL_LINT}

ukphy_subr.o: $S/dev/mii/ukphy_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xmphy.ln: $S/dev/mii/xmphy.c
	${NORMAL_LINT}

xmphy.o: $S/dev/mii/xmphy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mlx.ln: $S/dev/mlx/mlx.c
	${NORMAL_LINT}

mlx.o: $S/dev/mlx/mlx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mlx_disk.ln: $S/dev/mlx/mlx_disk.c
	${NORMAL_LINT}

mlx_disk.o: $S/dev/mlx/mlx_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mlx_pci.ln: $S/dev/mlx/mlx_pci.c
	${NORMAL_LINT}

mlx_pci.o: $S/dev/mlx/mlx_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mly.ln: $S/dev/mly/mly.c
	${NORMAL_LINT}

mly.o: $S/dev/mly/mly.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mmcbr_if.ln: $S/dev/mmc/mmcbr_if.m
	${NORMAL_LINT}

mmcbr_if.o: $S/dev/mmc/mmcbr_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mmcbus_if.ln: $S/dev/mmc/mmcbus_if.m
	${NORMAL_LINT}

mmcbus_if.o: $S/dev/mmc/mmcbus_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpt.ln: $S/dev/mpt/mpt.c
	${NORMAL_LINT}

mpt.o: $S/dev/mpt/mpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpt_cam.ln: $S/dev/mpt/mpt_cam.c
	${NORMAL_LINT}

mpt_cam.o: $S/dev/mpt/mpt_cam.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpt_debug.ln: $S/dev/mpt/mpt_debug.c
	${NORMAL_LINT}

mpt_debug.o: $S/dev/mpt/mpt_debug.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpt_pci.ln: $S/dev/mpt/mpt_pci.c
	${NORMAL_LINT}

mpt_pci.o: $S/dev/mpt/mpt_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpt_raid.ln: $S/dev/mpt/mpt_raid.c
	${NORMAL_LINT}

mpt_raid.o: $S/dev/mpt/mpt_raid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpt_user.ln: $S/dev/mpt/mpt_user.c
	${NORMAL_LINT}

mpt_user.o: $S/dev/mpt/mpt_user.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_msk.ln: $S/dev/msk/if_msk.c
	${NORMAL_LINT}

if_msk.o: $S/dev/msk/if_msk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ncr53c500.ln: $S/dev/ncv/ncr53c500.c
	${NORMAL_LINT}

ncr53c500.o: $S/dev/ncv/ncr53c500.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ncr53c500_pccard.ln: $S/dev/ncv/ncr53c500_pccard.c
	${NORMAL_LINT}

ncr53c500_pccard.o: $S/dev/ncv/ncr53c500_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_nge.ln: $S/dev/nge/if_nge.c
	${NORMAL_LINT}

if_nge.o: $S/dev/nge/if_nge.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsp.ln: $S/dev/nsp/nsp.c
	${NORMAL_LINT}

nsp.o: $S/dev/nsp/nsp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nsp_pccard.ln: $S/dev/nsp/nsp_pccard.c
	${NORMAL_LINT}

nsp_pccard.o: $S/dev/nsp/nsp_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

null.ln: $S/dev/null/null.c
	${NORMAL_LINT}

null.o: $S/dev/null/null.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

card_if.ln: $S/dev/pccard/card_if.m
	${NORMAL_LINT}

card_if.o: $S/dev/pccard/card_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccard.ln: $S/dev/pccard/pccard.c
	${NORMAL_LINT}

pccard.o: $S/dev/pccard/pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccard_cis.ln: $S/dev/pccard/pccard_cis.c
	${NORMAL_LINT}

pccard_cis.o: $S/dev/pccard/pccard_cis.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccard_cis_quirks.ln: $S/dev/pccard/pccard_cis_quirks.c
	${NORMAL_LINT}

pccard_cis_quirks.o: $S/dev/pccard/pccard_cis_quirks.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccard_device.ln: $S/dev/pccard/pccard_device.c
	${NORMAL_LINT}

pccard_device.o: $S/dev/pccard/pccard_device.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

power_if.ln: $S/dev/pccard/power_if.m
	${NORMAL_LINT}

power_if.o: $S/dev/pccard/power_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccbb.ln: $S/dev/pccbb/pccbb.c
	${NORMAL_LINT}

pccbb.o: $S/dev/pccbb/pccbb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccbb_isa.ln: $S/dev/pccbb/pccbb_isa.c
	${NORMAL_LINT}

pccbb_isa.o: $S/dev/pccbb/pccbb_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pccbb_pci.ln: $S/dev/pccbb/pccbb_pci.c
	${NORMAL_LINT}

pccbb_pci.o: $S/dev/pccbb/pccbb_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

eisa_pci.ln: $S/dev/pci/eisa_pci.c
	${NORMAL_LINT}

eisa_pci.o: $S/dev/pci/eisa_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fixup_pci.ln: $S/dev/pci/fixup_pci.c
	${NORMAL_LINT}

fixup_pci.o: $S/dev/pci/fixup_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hostb_pci.ln: $S/dev/pci/hostb_pci.c
	${NORMAL_LINT}

hostb_pci.o: $S/dev/pci/hostb_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ignore_pci.ln: $S/dev/pci/ignore_pci.c
	${NORMAL_LINT}

ignore_pci.o: $S/dev/pci/ignore_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isa_pci.ln: $S/dev/pci/isa_pci.c
	${NORMAL_LINT}

isa_pci.o: $S/dev/pci/isa_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci.ln: $S/dev/pci/pci.c
	${NORMAL_LINT}

pci.o: $S/dev/pci/pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci_if.ln: $S/dev/pci/pci_if.m
	${NORMAL_LINT}

pci_if.o: $S/dev/pci/pci_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci_pci.ln: $S/dev/pci/pci_pci.c
	${NORMAL_LINT}

pci_pci.o: $S/dev/pci/pci_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci_user.ln: $S/dev/pci/pci_user.c
	${NORMAL_LINT}

pci_user.o: $S/dev/pci/pci_user.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pcib_if.ln: $S/dev/pci/pcib_if.m
	${NORMAL_LINT}

pcib_if.o: $S/dev/pci/pcib_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vga_pci.ln: $S/dev/pci/vga_pci.c
	${NORMAL_LINT}

vga_pci.o: $S/dev/pci/vga_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_pcn.ln: $S/dev/pcn/if_pcn.c
	${NORMAL_LINT}

if_pcn.o: $S/dev/pcn/if_pcn.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_plip.ln: $S/dev/ppbus/if_plip.c
	${NORMAL_LINT}

if_plip.o: $S/dev/ppbus/if_plip.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

lpt.ln: $S/dev/ppbus/lpt.c
	${NORMAL_LINT}

lpt.o: $S/dev/ppbus/lpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppb_1284.ln: $S/dev/ppbus/ppb_1284.c
	${NORMAL_LINT}

ppb_1284.o: $S/dev/ppbus/ppb_1284.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppb_base.ln: $S/dev/ppbus/ppb_base.c
	${NORMAL_LINT}

ppb_base.o: $S/dev/ppbus/ppb_base.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppb_msq.ln: $S/dev/ppbus/ppb_msq.c
	${NORMAL_LINT}

ppb_msq.o: $S/dev/ppbus/ppb_msq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppbconf.ln: $S/dev/ppbus/ppbconf.c
	${NORMAL_LINT}

ppbconf.o: $S/dev/ppbus/ppbconf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppbus_if.ln: $S/dev/ppbus/ppbus_if.m
	${NORMAL_LINT}

ppbus_if.o: $S/dev/ppbus/ppbus_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppi.ln: $S/dev/ppbus/ppi.c
	${NORMAL_LINT}

ppi.o: $S/dev/ppbus/ppi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppc.ln: $S/dev/ppc/ppc.c
	${NORMAL_LINT}

ppc.o: $S/dev/ppc/ppc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppc_acpi.ln: $S/dev/ppc/ppc_acpi.c
	${NORMAL_LINT}

ppc_acpi.o: $S/dev/ppc/ppc_acpi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppc_isa.ln: $S/dev/ppc/ppc_isa.c
	${NORMAL_LINT}

ppc_isa.o: $S/dev/ppc/ppc_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ppc_pci.ln: $S/dev/ppc/ppc_pci.c
	${NORMAL_LINT}

ppc_pci.o: $S/dev/ppc/ppc_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pst-iop.ln: $S/dev/pst/pst-iop.c
	${NORMAL_LINT}

pst-iop.o: $S/dev/pst/pst-iop.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pst-pci.ln: $S/dev/pst/pst-pci.c
	${NORMAL_LINT}

pst-pci.o: $S/dev/pst/pst-pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pst-raid.ln: $S/dev/pst/pst-raid.c
	${NORMAL_LINT}

pst-raid.o: $S/dev/pst/pst-raid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rt2560.ln: $S/dev/ral/rt2560.c
	${NORMAL_LINT}

rt2560.o: $S/dev/ral/rt2560.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rt2661.ln: $S/dev/ral/rt2661.c
	${NORMAL_LINT}

rt2661.o: $S/dev/ral/rt2661.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ral_pci.ln: $S/dev/ral/if_ral_pci.c
	${NORMAL_LINT}

if_ral_pci.o: $S/dev/ral/if_ral_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

harvest.ln: $S/dev/random/harvest.c
	${NORMAL_LINT}

harvest.o: $S/dev/random/harvest.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hash.ln: $S/dev/random/hash.c
	${NORMAL_LINT}

hash.o: $S/dev/random/hash.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

probe.ln: $S/dev/random/probe.c
	${NORMAL_LINT}

probe.o: $S/dev/random/probe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

randomdev.ln: $S/dev/random/randomdev.c
	${NORMAL_LINT}

randomdev.o: $S/dev/random/randomdev.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

randomdev_soft.ln: $S/dev/random/randomdev_soft.c
	${NORMAL_LINT}

randomdev_soft.o: $S/dev/random/randomdev_soft.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

yarrow.ln: $S/dev/random/yarrow.c
	${NORMAL_LINT}

yarrow.o: $S/dev/random/yarrow.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_re.ln: $S/dev/re/if_re.c
	${NORMAL_LINT}

if_re.o: $S/dev/re/if_re.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_sf.ln: $S/dev/sf/if_sf.c
	${NORMAL_LINT}

if_sf.o: $S/dev/sf/if_sf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_sis.ln: $S/dev/sis/if_sis.c
	${NORMAL_LINT}

if_sis.o: $S/dev/sis/if_sis.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_sk.ln: $S/dev/sk/if_sk.c
	${NORMAL_LINT}

if_sk.o: $S/dev/sk/if_sk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_sn.ln: $S/dev/sn/if_sn.c
	${NORMAL_LINT}

if_sn.o: $S/dev/sn/if_sn.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_sn_isa.ln: $S/dev/sn/if_sn_isa.c
	${NORMAL_LINT}

if_sn_isa.o: $S/dev/sn/if_sn_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_sn_pccard.ln: $S/dev/sn/if_sn_pccard.c
	${NORMAL_LINT}

if_sn_pccard.o: $S/dev/sn/if_sn_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ste.ln: $S/dev/ste/if_ste.c
	${NORMAL_LINT}

if_ste.o: $S/dev/ste/if_ste.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tmc18c30.ln: $S/dev/stg/tmc18c30.c
	${NORMAL_LINT}

tmc18c30.o: $S/dev/stg/tmc18c30.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tmc18c30_isa.ln: $S/dev/stg/tmc18c30_isa.c
	${NORMAL_LINT}

tmc18c30_isa.o: $S/dev/stg/tmc18c30_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tmc18c30_pccard.ln: $S/dev/stg/tmc18c30_pccard.c
	${NORMAL_LINT}

tmc18c30_pccard.o: $S/dev/stg/tmc18c30_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tmc18c30_pci.ln: $S/dev/stg/tmc18c30_pci.c
	${NORMAL_LINT}

tmc18c30_pci.o: $S/dev/stg/tmc18c30_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tmc18c30_subr.ln: $S/dev/stg/tmc18c30_subr.c
	${NORMAL_LINT}

tmc18c30_subr.o: $S/dev/stg/tmc18c30_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_stge.ln: $S/dev/stge/if_stge.c
	${NORMAL_LINT}

if_stge.o: $S/dev/stge/if_stge.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sym_hipd.ln: $S/dev/sym/sym_hipd.c $S/dev/sym/sym_{conf,defs}.h
	${NORMAL_LINT}

sym_hipd.o: $S/dev/sym/sym_hipd.c $S/dev/sym/sym_{conf,defs}.h
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

schistory.ln: $S/dev/syscons/schistory.c
	${NORMAL_LINT}

schistory.o: $S/dev/syscons/schistory.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scmouse.ln: $S/dev/syscons/scmouse.c
	${NORMAL_LINT}

scmouse.o: $S/dev/syscons/scmouse.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scterm.ln: $S/dev/syscons/scterm.c
	${NORMAL_LINT}

scterm.o: $S/dev/syscons/scterm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scvidctl.ln: $S/dev/syscons/scvidctl.c
	${NORMAL_LINT}

scvidctl.o: $S/dev/syscons/scvidctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

syscons.ln: $S/dev/syscons/syscons.c
	${NORMAL_LINT}

syscons.o: $S/dev/syscons/syscons.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sysmouse.ln: $S/dev/syscons/sysmouse.c
	${NORMAL_LINT}

sysmouse.o: $S/dev/syscons/sysmouse.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ti.ln: $S/dev/ti/if_ti.c
	${NORMAL_LINT}

if_ti.o: $S/dev/ti/if_ti.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_tl.ln: $S/dev/tl/if_tl.c
	${NORMAL_LINT}

if_tl.o: $S/dev/tl/if_tl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

trm.ln: $S/dev/trm/trm.c
	${NORMAL_LINT}

trm.o: $S/dev/trm/trm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tw_cl_init.ln: $S/dev/twa/tw_cl_init.c
	${NORMAL_LINT}

tw_cl_init.o: $S/dev/twa/tw_cl_init.c
	${NORMAL_C} -I$S/dev/twa

tw_cl_intr.ln: $S/dev/twa/tw_cl_intr.c
	${NORMAL_LINT}

tw_cl_intr.o: $S/dev/twa/tw_cl_intr.c
	${NORMAL_C} -I$S/dev/twa

tw_cl_io.ln: $S/dev/twa/tw_cl_io.c
	${NORMAL_LINT}

tw_cl_io.o: $S/dev/twa/tw_cl_io.c
	${NORMAL_C} -I$S/dev/twa

tw_cl_misc.ln: $S/dev/twa/tw_cl_misc.c
	${NORMAL_LINT}

tw_cl_misc.o: $S/dev/twa/tw_cl_misc.c
	${NORMAL_C} -I$S/dev/twa

tw_osl_cam.ln: $S/dev/twa/tw_osl_cam.c
	${NORMAL_LINT}

tw_osl_cam.o: $S/dev/twa/tw_osl_cam.c
	${NORMAL_C} -I$S/dev/twa

tw_osl_freebsd.ln: $S/dev/twa/tw_osl_freebsd.c
	${NORMAL_LINT}

tw_osl_freebsd.o: $S/dev/twa/tw_osl_freebsd.c
	${NORMAL_C} -I$S/dev/twa

twe.ln: $S/dev/twe/twe.c
	${NORMAL_LINT}

twe.o: $S/dev/twe/twe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

twe_freebsd.ln: $S/dev/twe/twe_freebsd.c
	${NORMAL_LINT}

twe_freebsd.o: $S/dev/twe/twe_freebsd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_tx.ln: $S/dev/tx/if_tx.c
	${NORMAL_LINT}

if_tx.o: $S/dev/tx/if_tx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_txp.ln: $S/dev/txp/if_txp.c
	${NORMAL_LINT}

if_txp.o: $S/dev/txp/if_txp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_bus_acpi.ln: $S/dev/uart/uart_bus_acpi.c
	${NORMAL_LINT}

uart_bus_acpi.o: $S/dev/uart/uart_bus_acpi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_bus_isa.ln: $S/dev/uart/uart_bus_isa.c
	${NORMAL_LINT}

uart_bus_isa.o: $S/dev/uart/uart_bus_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_bus_pccard.ln: $S/dev/uart/uart_bus_pccard.c
	${NORMAL_LINT}

uart_bus_pccard.o: $S/dev/uart/uart_bus_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_bus_pci.ln: $S/dev/uart/uart_bus_pci.c
	${NORMAL_LINT}

uart_bus_pci.o: $S/dev/uart/uart_bus_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_core.ln: $S/dev/uart/uart_core.c
	${NORMAL_LINT}

uart_core.o: $S/dev/uart/uart_core.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_dev_ns8250.ln: $S/dev/uart/uart_dev_ns8250.c
	${NORMAL_LINT}

uart_dev_ns8250.o: $S/dev/uart/uart_dev_ns8250.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_if.ln: $S/dev/uart/uart_if.m
	${NORMAL_LINT}

uart_if.o: $S/dev/uart/uart_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_subr.ln: $S/dev/uart/uart_subr.c
	${NORMAL_LINT}

uart_subr.o: $S/dev/uart/uart_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_tty.ln: $S/dev/uart/uart_tty.c
	${NORMAL_LINT}

uart_tty.o: $S/dev/uart/uart_tty.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ehci.ln: $S/dev/usb/controller/ehci.c
	${NORMAL_LINT}

ehci.o: $S/dev/usb/controller/ehci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ehci_pci.ln: $S/dev/usb/controller/ehci_pci.c
	${NORMAL_LINT}

ehci_pci.o: $S/dev/usb/controller/ehci_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ohci.ln: $S/dev/usb/controller/ohci.c
	${NORMAL_LINT}

ohci.o: $S/dev/usb/controller/ohci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ohci_pci.ln: $S/dev/usb/controller/ohci_pci.c
	${NORMAL_LINT}

ohci_pci.o: $S/dev/usb/controller/ohci_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uhci.ln: $S/dev/usb/controller/uhci.c
	${NORMAL_LINT}

uhci.o: $S/dev/usb/controller/uhci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uhci_pci.ln: $S/dev/usb/controller/uhci_pci.c
	${NORMAL_LINT}

uhci_pci.o: $S/dev/usb/controller/uhci_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_controller.ln: $S/dev/usb/controller/usb_controller.c
	${NORMAL_LINT}

usb_controller.o: $S/dev/usb/controller/usb_controller.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

umass.ln: $S/dev/usb/storage/umass.c
	${NORMAL_LINT}

umass.o: $S/dev/usb/storage/umass.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

urio.ln: $S/dev/usb/storage/urio.c
	${NORMAL_LINT}

urio.o: $S/dev/usb/storage/urio.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_busdma.ln: $S/dev/usb/usb_busdma.c
	${NORMAL_LINT}

usb_busdma.o: $S/dev/usb/usb_busdma.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_compat_linux.ln: $S/dev/usb/usb_compat_linux.c
	${NORMAL_LINT}

usb_compat_linux.o: $S/dev/usb/usb_compat_linux.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_core.ln: $S/dev/usb/usb_core.c
	${NORMAL_LINT}

usb_core.o: $S/dev/usb/usb_core.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_debug.ln: $S/dev/usb/usb_debug.c
	${NORMAL_LINT}

usb_debug.o: $S/dev/usb/usb_debug.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_dev.ln: $S/dev/usb/usb_dev.c
	${NORMAL_LINT}

usb_dev.o: $S/dev/usb/usb_dev.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_device.ln: $S/dev/usb/usb_device.c
	${NORMAL_LINT}

usb_device.o: $S/dev/usb/usb_device.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_dynamic.ln: $S/dev/usb/usb_dynamic.c
	${NORMAL_LINT}

usb_dynamic.o: $S/dev/usb/usb_dynamic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_error.ln: $S/dev/usb/usb_error.c
	${NORMAL_LINT}

usb_error.o: $S/dev/usb/usb_error.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_generic.ln: $S/dev/usb/usb_generic.c
	${NORMAL_LINT}

usb_generic.o: $S/dev/usb/usb_generic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_handle_request.ln: $S/dev/usb/usb_handle_request.c
	${NORMAL_LINT}

usb_handle_request.o: $S/dev/usb/usb_handle_request.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_hid.ln: $S/dev/usb/usb_hid.c
	${NORMAL_LINT}

usb_hid.o: $S/dev/usb/usb_hid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_hub.ln: $S/dev/usb/usb_hub.c
	${NORMAL_LINT}

usb_hub.o: $S/dev/usb/usb_hub.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_if.ln: $S/dev/usb/usb_if.m
	${NORMAL_LINT}

usb_if.o: $S/dev/usb/usb_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_lookup.ln: $S/dev/usb/usb_lookup.c
	${NORMAL_LINT}

usb_lookup.o: $S/dev/usb/usb_lookup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_mbuf.ln: $S/dev/usb/usb_mbuf.c
	${NORMAL_LINT}

usb_mbuf.o: $S/dev/usb/usb_mbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_msctest.ln: $S/dev/usb/usb_msctest.c
	${NORMAL_LINT}

usb_msctest.o: $S/dev/usb/usb_msctest.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_parse.ln: $S/dev/usb/usb_parse.c
	${NORMAL_LINT}

usb_parse.o: $S/dev/usb/usb_parse.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_process.ln: $S/dev/usb/usb_process.c
	${NORMAL_LINT}

usb_process.o: $S/dev/usb/usb_process.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_request.ln: $S/dev/usb/usb_request.c
	${NORMAL_LINT}

usb_request.o: $S/dev/usb/usb_request.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_transfer.ln: $S/dev/usb/usb_transfer.c
	${NORMAL_LINT}

usb_transfer.o: $S/dev/usb/usb_transfer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_util.ln: $S/dev/usb/usb_util.c
	${NORMAL_LINT}

usb_util.o: $S/dev/usb/usb_util.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_aue.ln: $S/dev/usb/net/if_aue.c
	${NORMAL_LINT}

if_aue.o: $S/dev/usb/net/if_aue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_axe.ln: $S/dev/usb/net/if_axe.c
	${NORMAL_LINT}

if_axe.o: $S/dev/usb/net/if_axe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_cdce.ln: $S/dev/usb/net/if_cdce.c
	${NORMAL_LINT}

if_cdce.o: $S/dev/usb/net/if_cdce.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_cue.ln: $S/dev/usb/net/if_cue.c
	${NORMAL_LINT}

if_cue.o: $S/dev/usb/net/if_cue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_kue.ln: $S/dev/usb/net/if_kue.c
	${NORMAL_LINT}

if_kue.o: $S/dev/usb/net/if_kue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_rue.ln: $S/dev/usb/net/if_rue.c
	${NORMAL_LINT}

if_rue.o: $S/dev/usb/net/if_rue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_udav.ln: $S/dev/usb/net/if_udav.c
	${NORMAL_LINT}

if_udav.o: $S/dev/usb/net/if_udav.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_ethernet.ln: $S/dev/usb/net/usb_ethernet.c
	${NORMAL_LINT}

usb_ethernet.o: $S/dev/usb/net/usb_ethernet.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_rum.ln: $S/dev/usb/wlan/if_rum.c
	${NORMAL_LINT}

if_rum.o: $S/dev/usb/wlan/if_rum.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_uath.ln: $S/dev/usb/wlan/if_uath.c
	${NORMAL_LINT}

if_uath.o: $S/dev/usb/wlan/if_uath.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ural.ln: $S/dev/usb/wlan/if_ural.c
	${NORMAL_LINT}

if_ural.o: $S/dev/usb/wlan/if_ural.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_zyd.ln: $S/dev/usb/wlan/if_zyd.c
	${NORMAL_LINT}

if_zyd.o: $S/dev/usb/wlan/if_zyd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

u3g.ln: $S/dev/usb/serial/u3g.c
	${NORMAL_LINT}

u3g.o: $S/dev/usb/serial/u3g.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uark.ln: $S/dev/usb/serial/uark.c
	${NORMAL_LINT}

uark.o: $S/dev/usb/serial/uark.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ubsa.ln: $S/dev/usb/serial/ubsa.c
	${NORMAL_LINT}

ubsa.o: $S/dev/usb/serial/ubsa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uftdi.ln: $S/dev/usb/serial/uftdi.c
	${NORMAL_LINT}

uftdi.o: $S/dev/usb/serial/uftdi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipaq.ln: $S/dev/usb/serial/uipaq.c
	${NORMAL_LINT}

uipaq.o: $S/dev/usb/serial/uipaq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ulpt.ln: $S/dev/usb/serial/ulpt.c
	${NORMAL_LINT}

ulpt.o: $S/dev/usb/serial/ulpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uplcom.ln: $S/dev/usb/serial/uplcom.c
	${NORMAL_LINT}

uplcom.o: $S/dev/usb/serial/uplcom.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uslcom.ln: $S/dev/usb/serial/uslcom.c
	${NORMAL_LINT}

uslcom.o: $S/dev/usb/serial/uslcom.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uvisor.ln: $S/dev/usb/serial/uvisor.c
	${NORMAL_LINT}

uvisor.o: $S/dev/usb/serial/uvisor.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uvscom.ln: $S/dev/usb/serial/uvscom.c
	${NORMAL_LINT}

uvscom.o: $S/dev/usb/serial/uvscom.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_serial.ln: $S/dev/usb/serial/usb_serial.c
	${NORMAL_LINT}

usb_serial.o: $S/dev/usb/serial/usb_serial.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uhid.ln: $S/dev/usb/input/uhid.c
	${NORMAL_LINT}

uhid.o: $S/dev/usb/input/uhid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ukbd.ln: $S/dev/usb/input/ukbd.c
	${NORMAL_LINT}

ukbd.o: $S/dev/usb/input/ukbd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ums.ln: $S/dev/usb/input/ums.c
	${NORMAL_LINT}

ums.o: $S/dev/usb/input/ums.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

usb_quirk.ln: $S/dev/usb/quirk/usb_quirk.c
	${NORMAL_LINT}

usb_quirk.o: $S/dev/usb/quirk/usb_quirk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_vge.ln: $S/dev/vge/if_vge.c
	${NORMAL_LINT}

if_vge.o: $S/dev/vge/if_vge.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_vr.ln: $S/dev/vr/if_vr.c
	${NORMAL_LINT}

if_vr.o: $S/dev/vr/if_vr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_vx.ln: $S/dev/vx/if_vx.c
	${NORMAL_LINT}

if_vx.o: $S/dev/vx/if_vx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_vx_eisa.ln: $S/dev/vx/if_vx_eisa.c
	${NORMAL_LINT}

if_vx_eisa.o: $S/dev/vx/if_vx_eisa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_vx_pci.ln: $S/dev/vx/if_vx_pci.c
	${NORMAL_LINT}

if_vx_pci.o: $S/dev/vx/if_vx_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

watchdog.ln: $S/dev/watchdog/watchdog.c
	${NORMAL_LINT}

watchdog.o: $S/dev/watchdog/watchdog.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_wb.ln: $S/dev/wb/if_wb.c
	${NORMAL_LINT}

if_wb.o: $S/dev/wb/if_wb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_wi.ln: $S/dev/wi/if_wi.c
	${NORMAL_LINT}

if_wi.o: $S/dev/wi/if_wi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_wi_pccard.ln: $S/dev/wi/if_wi_pccard.c
	${NORMAL_LINT}

if_wi_pccard.o: $S/dev/wi/if_wi_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_wi_pci.ln: $S/dev/wi/if_wi_pci.c
	${NORMAL_LINT}

if_wi_pci.o: $S/dev/wi/if_wi_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_xe.ln: $S/dev/xe/if_xe.c
	${NORMAL_LINT}

if_xe.o: $S/dev/xe/if_xe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_xe_pccard.ln: $S/dev/xe/if_xe_pccard.c
	${NORMAL_LINT}

if_xe_pccard.o: $S/dev/xe/if_xe_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_xl.ln: $S/dev/xl/if_xl.c
	${NORMAL_LINT}

if_xl.o: $S/dev/xl/if_xl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dead_vnops.ln: $S/fs/deadfs/dead_vnops.c
	${NORMAL_LINT}

dead_vnops.o: $S/fs/deadfs/dead_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

devfs_devs.ln: $S/fs/devfs/devfs_devs.c
	${NORMAL_LINT}

devfs_devs.o: $S/fs/devfs/devfs_devs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

devfs_rule.ln: $S/fs/devfs/devfs_rule.c
	${NORMAL_LINT}

devfs_rule.o: $S/fs/devfs/devfs_rule.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

devfs_vfsops.ln: $S/fs/devfs/devfs_vfsops.c
	${NORMAL_LINT}

devfs_vfsops.o: $S/fs/devfs/devfs_vfsops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

devfs_vnops.ln: $S/fs/devfs/devfs_vnops.c
	${NORMAL_LINT}

devfs_vnops.o: $S/fs/devfs/devfs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fifo_vnops.ln: $S/fs/fifofs/fifo_vnops.c
	${NORMAL_LINT}

fifo_vnops.o: $S/fs/fifofs/fifo_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_conv.ln: $S/fs/msdosfs/msdosfs_conv.c
	${NORMAL_LINT}

msdosfs_conv.o: $S/fs/msdosfs/msdosfs_conv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_denode.ln: $S/fs/msdosfs/msdosfs_denode.c
	${NORMAL_LINT}

msdosfs_denode.o: $S/fs/msdosfs/msdosfs_denode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_fat.ln: $S/fs/msdosfs/msdosfs_fat.c
	${NORMAL_LINT}

msdosfs_fat.o: $S/fs/msdosfs/msdosfs_fat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_fileno.ln: $S/fs/msdosfs/msdosfs_fileno.c
	${NORMAL_LINT}

msdosfs_fileno.o: $S/fs/msdosfs/msdosfs_fileno.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_lookup.ln: $S/fs/msdosfs/msdosfs_lookup.c
	${NORMAL_LINT}

msdosfs_lookup.o: $S/fs/msdosfs/msdosfs_lookup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_vfsops.ln: $S/fs/msdosfs/msdosfs_vfsops.c
	${NORMAL_LINT}

msdosfs_vfsops.o: $S/fs/msdosfs/msdosfs_vfsops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msdosfs_vnops.ln: $S/fs/msdosfs/msdosfs_vnops.c
	${NORMAL_LINT}

msdosfs_vnops.o: $S/fs/msdosfs/msdosfs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs.ln: $S/fs/procfs/procfs.c
	${NORMAL_LINT}

procfs.o: $S/fs/procfs/procfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_ctl.ln: $S/fs/procfs/procfs_ctl.c
	${NORMAL_LINT}

procfs_ctl.o: $S/fs/procfs/procfs_ctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_dbregs.ln: $S/fs/procfs/procfs_dbregs.c
	${NORMAL_LINT}

procfs_dbregs.o: $S/fs/procfs/procfs_dbregs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_fpregs.ln: $S/fs/procfs/procfs_fpregs.c
	${NORMAL_LINT}

procfs_fpregs.o: $S/fs/procfs/procfs_fpregs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_ioctl.ln: $S/fs/procfs/procfs_ioctl.c
	${NORMAL_LINT}

procfs_ioctl.o: $S/fs/procfs/procfs_ioctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_map.ln: $S/fs/procfs/procfs_map.c
	${NORMAL_LINT}

procfs_map.o: $S/fs/procfs/procfs_map.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_mem.ln: $S/fs/procfs/procfs_mem.c
	${NORMAL_LINT}

procfs_mem.o: $S/fs/procfs/procfs_mem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_note.ln: $S/fs/procfs/procfs_note.c
	${NORMAL_LINT}

procfs_note.o: $S/fs/procfs/procfs_note.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_regs.ln: $S/fs/procfs/procfs_regs.c
	${NORMAL_LINT}

procfs_regs.o: $S/fs/procfs/procfs_regs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_rlimit.ln: $S/fs/procfs/procfs_rlimit.c
	${NORMAL_LINT}

procfs_rlimit.o: $S/fs/procfs/procfs_rlimit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_status.ln: $S/fs/procfs/procfs_status.c
	${NORMAL_LINT}

procfs_status.o: $S/fs/procfs/procfs_status.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

procfs_type.ln: $S/fs/procfs/procfs_type.c
	${NORMAL_LINT}

procfs_type.o: $S/fs/procfs/procfs_type.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pseudofs.ln: $S/fs/pseudofs/pseudofs.c
	${NORMAL_LINT}

pseudofs.o: $S/fs/pseudofs/pseudofs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pseudofs_fileno.ln: $S/fs/pseudofs/pseudofs_fileno.c
	${NORMAL_LINT}

pseudofs_fileno.o: $S/fs/pseudofs/pseudofs_fileno.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pseudofs_vncache.ln: $S/fs/pseudofs/pseudofs_vncache.c
	${NORMAL_LINT}

pseudofs_vncache.o: $S/fs/pseudofs/pseudofs_vncache.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pseudofs_vnops.ln: $S/fs/pseudofs/pseudofs_vnops.c
	${NORMAL_LINT}

pseudofs_vnops.o: $S/fs/pseudofs/pseudofs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_ctl.ln: $S/geom/geom_ctl.c
	${NORMAL_LINT}

geom_ctl.o: $S/geom/geom_ctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_dev.ln: $S/geom/geom_dev.c
	${NORMAL_LINT}

geom_dev.o: $S/geom/geom_dev.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_disk.ln: $S/geom/geom_disk.c
	${NORMAL_LINT}

geom_disk.o: $S/geom/geom_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_dump.ln: $S/geom/geom_dump.c
	${NORMAL_LINT}

geom_dump.o: $S/geom/geom_dump.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_event.ln: $S/geom/geom_event.c
	${NORMAL_LINT}

geom_event.o: $S/geom/geom_event.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_io.ln: $S/geom/geom_io.c
	${NORMAL_LINT}

geom_io.o: $S/geom/geom_io.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_kern.ln: $S/geom/geom_kern.c
	${NORMAL_LINT}

geom_kern.o: $S/geom/geom_kern.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_slice.ln: $S/geom/geom_slice.c
	${NORMAL_LINT}

geom_slice.o: $S/geom/geom_slice.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_subr.ln: $S/geom/geom_subr.c
	${NORMAL_LINT}

geom_subr.o: $S/geom/geom_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

geom_vfs.ln: $S/geom/geom_vfs.c
	${NORMAL_LINT}

geom_vfs.o: $S/geom/geom_vfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label.ln: $S/geom/label/g_label.c
	${NORMAL_LINT}

g_label.o: $S/geom/label/g_label.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_ext2fs.ln: $S/geom/label/g_label_ext2fs.c
	${NORMAL_LINT}

g_label_ext2fs.o: $S/geom/label/g_label_ext2fs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_iso9660.ln: $S/geom/label/g_label_iso9660.c
	${NORMAL_LINT}

g_label_iso9660.o: $S/geom/label/g_label_iso9660.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_msdosfs.ln: $S/geom/label/g_label_msdosfs.c
	${NORMAL_LINT}

g_label_msdosfs.o: $S/geom/label/g_label_msdosfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_ntfs.ln: $S/geom/label/g_label_ntfs.c
	${NORMAL_LINT}

g_label_ntfs.o: $S/geom/label/g_label_ntfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_reiserfs.ln: $S/geom/label/g_label_reiserfs.c
	${NORMAL_LINT}

g_label_reiserfs.o: $S/geom/label/g_label_reiserfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_ufs.ln: $S/geom/label/g_label_ufs.c
	${NORMAL_LINT}

g_label_ufs.o: $S/geom/label/g_label_ufs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_label_gpt.ln: $S/geom/label/g_label_gpt.c
	${NORMAL_LINT}

g_label_gpt.o: $S/geom/label/g_label_gpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_part.ln: $S/geom/part/g_part.c
	${NORMAL_LINT}

g_part.o: $S/geom/part/g_part.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_part_if.ln: $S/geom/part/g_part_if.m
	${NORMAL_LINT}

g_part_if.o: $S/geom/part/g_part_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_part_bsd.ln: $S/geom/part/g_part_bsd.c
	${NORMAL_LINT}

g_part_bsd.o: $S/geom/part/g_part_bsd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_part_ebr.ln: $S/geom/part/g_part_ebr.c
	${NORMAL_LINT}

g_part_ebr.o: $S/geom/part/g_part_ebr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_part_gpt.ln: $S/geom/part/g_part_gpt.c
	${NORMAL_LINT}

g_part_gpt.o: $S/geom/part/g_part_gpt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

g_part_mbr.ln: $S/geom/part/g_part_mbr.c
	${NORMAL_LINT}

g_part_mbr.o: $S/geom/part/g_part_mbr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isa_if.ln: $S/isa/isa_if.m
	${NORMAL_LINT}

isa_if.o: $S/isa/isa_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isa_common.ln: $S/isa/isa_common.c
	${NORMAL_LINT}

isa_common.o: $S/isa/isa_common.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isahint.ln: $S/isa/isahint.c
	${NORMAL_LINT}

isahint.o: $S/isa/isahint.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

orm.ln: $S/isa/orm.c
	${NORMAL_LINT}

orm.o: $S/isa/orm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pnp.ln: $S/isa/pnp.c
	${NORMAL_LINT}

pnp.o: $S/isa/pnp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pnpparse.ln: $S/isa/pnpparse.c
	${NORMAL_LINT}

pnpparse.o: $S/isa/pnpparse.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_bmap.ln: $S/fs/cd9660/cd9660_bmap.c
	${NORMAL_LINT}

cd9660_bmap.o: $S/fs/cd9660/cd9660_bmap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_lookup.ln: $S/fs/cd9660/cd9660_lookup.c
	${NORMAL_LINT}

cd9660_lookup.o: $S/fs/cd9660/cd9660_lookup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_node.ln: $S/fs/cd9660/cd9660_node.c
	${NORMAL_LINT}

cd9660_node.o: $S/fs/cd9660/cd9660_node.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_rrip.ln: $S/fs/cd9660/cd9660_rrip.c
	${NORMAL_LINT}

cd9660_rrip.o: $S/fs/cd9660/cd9660_rrip.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_util.ln: $S/fs/cd9660/cd9660_util.c
	${NORMAL_LINT}

cd9660_util.o: $S/fs/cd9660/cd9660_util.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_vfsops.ln: $S/fs/cd9660/cd9660_vfsops.c
	${NORMAL_LINT}

cd9660_vfsops.o: $S/fs/cd9660/cd9660_vfsops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cd9660_vnops.ln: $S/fs/cd9660/cd9660_vnops.c
	${NORMAL_LINT}

cd9660_vnops.o: $S/fs/cd9660/cd9660_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bus_if.ln: $S/kern/bus_if.m
	${NORMAL_LINT}

bus_if.o: $S/kern/bus_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

clock_if.ln: $S/kern/clock_if.m
	${NORMAL_LINT}

clock_if.o: $S/kern/clock_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

cpufreq_if.ln: $S/kern/cpufreq_if.m
	${NORMAL_LINT}

cpufreq_if.o: $S/kern/cpufreq_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

device_if.ln: $S/kern/device_if.m
	${NORMAL_LINT}

device_if.o: $S/kern/device_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

imgact_elf.ln: $S/kern/imgact_elf.c
	${NORMAL_LINT}

imgact_elf.o: $S/kern/imgact_elf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

imgact_shell.ln: $S/kern/imgact_shell.c
	${NORMAL_LINT}

imgact_shell.o: $S/kern/imgact_shell.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

init_main.ln: $S/kern/init_main.c
	${NORMAL_LINT}

init_main.o: $S/kern/init_main.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

init_sysent.ln: $S/kern/init_sysent.c
	${NORMAL_LINT}

init_sysent.o: $S/kern/init_sysent.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ksched.ln: $S/kern/ksched.c
	${NORMAL_LINT}

ksched.o: $S/kern/ksched.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_acct.ln: $S/kern/kern_acct.c
	${NORMAL_LINT}

kern_acct.o: $S/kern/kern_acct.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_clock.ln: $S/kern/kern_clock.c
	${NORMAL_LINT}

kern_clock.o: $S/kern/kern_clock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_condvar.ln: $S/kern/kern_condvar.c
	${NORMAL_LINT}

kern_condvar.o: $S/kern/kern_condvar.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_conf.ln: $S/kern/kern_conf.c
	${NORMAL_LINT}

kern_conf.o: $S/kern/kern_conf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_cons.ln: $S/kern/kern_cons.c
	${NORMAL_LINT}

kern_cons.o: $S/kern/kern_cons.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_cpu.ln: $S/kern/kern_cpu.c
	${NORMAL_LINT}

kern_cpu.o: $S/kern/kern_cpu.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_cpuset.ln: $S/kern/kern_cpuset.c
	${NORMAL_LINT}

kern_cpuset.o: $S/kern/kern_cpuset.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_context.ln: $S/kern/kern_context.c
	${NORMAL_LINT}

kern_context.o: $S/kern/kern_context.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_descrip.ln: $S/kern/kern_descrip.c
	${NORMAL_LINT}

kern_descrip.o: $S/kern/kern_descrip.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_environment.ln: $S/kern/kern_environment.c
	${NORMAL_LINT}

kern_environment.o: $S/kern/kern_environment.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_event.ln: $S/kern/kern_event.c
	${NORMAL_LINT}

kern_event.o: $S/kern/kern_event.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_exec.ln: $S/kern/kern_exec.c
	${NORMAL_LINT}

kern_exec.o: $S/kern/kern_exec.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_exit.ln: $S/kern/kern_exit.c
	${NORMAL_LINT}

kern_exit.o: $S/kern/kern_exit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_fail.ln: $S/kern/kern_fail.c
	${NORMAL_LINT}

kern_fail.o: $S/kern/kern_fail.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_fork.ln: $S/kern/kern_fork.c
	${NORMAL_LINT}

kern_fork.o: $S/kern/kern_fork.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_idle.ln: $S/kern/kern_idle.c
	${NORMAL_LINT}

kern_idle.o: $S/kern/kern_idle.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_intr.ln: $S/kern/kern_intr.c
	${NORMAL_LINT}

kern_intr.o: $S/kern/kern_intr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_jail.ln: $S/kern/kern_jail.c
	${NORMAL_LINT}

kern_jail.o: $S/kern/kern_jail.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_kthread.ln: $S/kern/kern_kthread.c
	${NORMAL_LINT}

kern_kthread.o: $S/kern/kern_kthread.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_ktrace.ln: $S/kern/kern_ktrace.c
	${NORMAL_LINT}

kern_ktrace.o: $S/kern/kern_ktrace.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_linker.ln: $S/kern/kern_linker.c
	${NORMAL_LINT}

kern_linker.o: $S/kern/kern_linker.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_lock.ln: $S/kern/kern_lock.c
	${NORMAL_LINT}

kern_lock.o: $S/kern/kern_lock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_lockf.ln: $S/kern/kern_lockf.c
	${NORMAL_LINT}

kern_lockf.o: $S/kern/kern_lockf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_malloc.ln: $S/kern/kern_malloc.c
	${NORMAL_LINT}

kern_malloc.o: $S/kern/kern_malloc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_mbuf.ln: $S/kern/kern_mbuf.c
	${NORMAL_LINT}

kern_mbuf.o: $S/kern/kern_mbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_mib.ln: $S/kern/kern_mib.c
	${NORMAL_LINT}

kern_mib.o: $S/kern/kern_mib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_module.ln: $S/kern/kern_module.c
	${NORMAL_LINT}

kern_module.o: $S/kern/kern_module.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_mtxpool.ln: $S/kern/kern_mtxpool.c
	${NORMAL_LINT}

kern_mtxpool.o: $S/kern/kern_mtxpool.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_mutex.ln: $S/kern/kern_mutex.c
	${NORMAL_LINT}

kern_mutex.o: $S/kern/kern_mutex.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_ntptime.ln: $S/kern/kern_ntptime.c
	${NORMAL_LINT}

kern_ntptime.o: $S/kern/kern_ntptime.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_osd.ln: $S/kern/kern_osd.c
	${NORMAL_LINT}

kern_osd.o: $S/kern/kern_osd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_physio.ln: $S/kern/kern_physio.c
	${NORMAL_LINT}

kern_physio.o: $S/kern/kern_physio.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_pmc.ln: $S/kern/kern_pmc.c
	${NORMAL_LINT}

kern_pmc.o: $S/kern/kern_pmc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_priv.ln: $S/kern/kern_priv.c
	${NORMAL_LINT}

kern_priv.o: $S/kern/kern_priv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_proc.ln: $S/kern/kern_proc.c
	${NORMAL_LINT}

kern_proc.o: $S/kern/kern_proc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_prot.ln: $S/kern/kern_prot.c
	${NORMAL_LINT}

kern_prot.o: $S/kern/kern_prot.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_resource.ln: $S/kern/kern_resource.c
	${NORMAL_LINT}

kern_resource.o: $S/kern/kern_resource.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_rmlock.ln: $S/kern/kern_rmlock.c
	${NORMAL_LINT}

kern_rmlock.o: $S/kern/kern_rmlock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_rwlock.ln: $S/kern/kern_rwlock.c
	${NORMAL_LINT}

kern_rwlock.o: $S/kern/kern_rwlock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_sema.ln: $S/kern/kern_sema.c
	${NORMAL_LINT}

kern_sema.o: $S/kern/kern_sema.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_shutdown.ln: $S/kern/kern_shutdown.c
	${NORMAL_LINT}

kern_shutdown.o: $S/kern/kern_shutdown.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_sig.ln: $S/kern/kern_sig.c
	${NORMAL_LINT}

kern_sig.o: $S/kern/kern_sig.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_subr.ln: $S/kern/kern_subr.c
	${NORMAL_LINT}

kern_subr.o: $S/kern/kern_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_switch.ln: $S/kern/kern_switch.c
	${NORMAL_LINT}

kern_switch.o: $S/kern/kern_switch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_sx.ln: $S/kern/kern_sx.c
	${NORMAL_LINT}

kern_sx.o: $S/kern/kern_sx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_synch.ln: $S/kern/kern_synch.c
	${NORMAL_LINT}

kern_synch.o: $S/kern/kern_synch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_syscalls.ln: $S/kern/kern_syscalls.c
	${NORMAL_LINT}

kern_syscalls.o: $S/kern/kern_syscalls.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_sysctl.ln: $S/kern/kern_sysctl.c
	${NORMAL_LINT}

kern_sysctl.o: $S/kern/kern_sysctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_tc.ln: $S/kern/kern_tc.c
	${NORMAL_LINT}

kern_tc.o: $S/kern/kern_tc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_thr.ln: $S/kern/kern_thr.c
	${NORMAL_LINT}

kern_thr.o: $S/kern/kern_thr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_thread.ln: $S/kern/kern_thread.c
	${NORMAL_LINT}

kern_thread.o: $S/kern/kern_thread.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_time.ln: $S/kern/kern_time.c
	${NORMAL_LINT}

kern_time.o: $S/kern/kern_time.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_timeout.ln: $S/kern/kern_timeout.c
	${NORMAL_LINT}

kern_timeout.o: $S/kern/kern_timeout.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_umtx.ln: $S/kern/kern_umtx.c
	${NORMAL_LINT}

kern_umtx.o: $S/kern/kern_umtx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_uuid.ln: $S/kern/kern_uuid.c
	${NORMAL_LINT}

kern_uuid.o: $S/kern/kern_uuid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kern_xxx.ln: $S/kern/kern_xxx.c
	${NORMAL_LINT}

kern_xxx.o: $S/kern/kern_xxx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

link_elf.ln: $S/kern/link_elf.c
	${NORMAL_LINT}

link_elf.o: $S/kern/link_elf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

linker_if.ln: $S/kern/linker_if.m
	${NORMAL_LINT}

linker_if.o: $S/kern/linker_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

md5c.ln: $S/kern/md5c.c
	${NORMAL_LINT}

md5c.o: $S/kern/md5c.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

p1003_1b.ln: $S/kern/p1003_1b.c
	${NORMAL_LINT}

p1003_1b.o: $S/kern/p1003_1b.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

posix4_mib.ln: $S/kern/posix4_mib.c
	${NORMAL_LINT}

posix4_mib.o: $S/kern/posix4_mib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sched_ule.ln: $S/kern/sched_ule.c
	${NORMAL_LINT}

sched_ule.o: $S/kern/sched_ule.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

serdev_if.ln: $S/kern/serdev_if.m
	${NORMAL_LINT}

serdev_if.o: $S/kern/serdev_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

stack_protector.ln: $S/kern/stack_protector.c
	${NORMAL_LINT}

stack_protector.o: $S/kern/stack_protector.c
	${NORMAL_C:N-fstack-protector*}

subr_acl_posix1e.ln: $S/kern/subr_acl_posix1e.c
	${NORMAL_LINT}

subr_acl_posix1e.o: $S/kern/subr_acl_posix1e.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_autoconf.ln: $S/kern/subr_autoconf.c
	${NORMAL_LINT}

subr_autoconf.o: $S/kern/subr_autoconf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_blist.ln: $S/kern/subr_blist.c
	${NORMAL_LINT}

subr_blist.o: $S/kern/subr_blist.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_bus.ln: $S/kern/subr_bus.c
	${NORMAL_LINT}

subr_bus.o: $S/kern/subr_bus.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_bufring.ln: $S/kern/subr_bufring.c
	${NORMAL_LINT}

subr_bufring.o: $S/kern/subr_bufring.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_clock.ln: $S/kern/subr_clock.c
	${NORMAL_LINT}

subr_clock.o: $S/kern/subr_clock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_devstat.ln: $S/kern/subr_devstat.c
	${NORMAL_LINT}

subr_devstat.o: $S/kern/subr_devstat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_disk.ln: $S/kern/subr_disk.c
	${NORMAL_LINT}

subr_disk.o: $S/kern/subr_disk.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_eventhandler.ln: $S/kern/subr_eventhandler.c
	${NORMAL_LINT}

subr_eventhandler.o: $S/kern/subr_eventhandler.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_fattime.ln: $S/kern/subr_fattime.c
	${NORMAL_LINT}

subr_fattime.o: $S/kern/subr_fattime.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_firmware.ln: $S/kern/subr_firmware.c
	${NORMAL_LINT}

subr_firmware.o: $S/kern/subr_firmware.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_hints.ln: $S/kern/subr_hints.c
	${NORMAL_LINT}

subr_hints.o: $S/kern/subr_hints.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_kdb.ln: $S/kern/subr_kdb.c
	${NORMAL_LINT}

subr_kdb.o: $S/kern/subr_kdb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_kobj.ln: $S/kern/subr_kobj.c
	${NORMAL_LINT}

subr_kobj.o: $S/kern/subr_kobj.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_lock.ln: $S/kern/subr_lock.c
	${NORMAL_LINT}

subr_lock.o: $S/kern/subr_lock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_log.ln: $S/kern/subr_log.c
	${NORMAL_LINT}

subr_log.o: $S/kern/subr_log.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_module.ln: $S/kern/subr_module.c
	${NORMAL_LINT}

subr_module.o: $S/kern/subr_module.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_msgbuf.ln: $S/kern/subr_msgbuf.c
	${NORMAL_LINT}

subr_msgbuf.o: $S/kern/subr_msgbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_param.ln: $S/kern/subr_param.c
	${NORMAL_LINT}

subr_param.o: $S/kern/subr_param.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_pcpu.ln: $S/kern/subr_pcpu.c
	${NORMAL_LINT}

subr_pcpu.o: $S/kern/subr_pcpu.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_power.ln: $S/kern/subr_power.c
	${NORMAL_LINT}

subr_power.o: $S/kern/subr_power.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_prf.ln: $S/kern/subr_prf.c
	${NORMAL_LINT}

subr_prf.o: $S/kern/subr_prf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_prof.ln: $S/kern/subr_prof.c
	${NORMAL_LINT}

subr_prof.o: $S/kern/subr_prof.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_rman.ln: $S/kern/subr_rman.c
	${NORMAL_LINT}

subr_rman.o: $S/kern/subr_rman.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_rtc.ln: $S/kern/subr_rtc.c
	${NORMAL_LINT}

subr_rtc.o: $S/kern/subr_rtc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_sbuf.ln: $S/kern/subr_sbuf.c
	${NORMAL_LINT}

subr_sbuf.o: $S/kern/subr_sbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_scanf.ln: $S/kern/subr_scanf.c
	${NORMAL_LINT}

subr_scanf.o: $S/kern/subr_scanf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_sglist.ln: $S/kern/subr_sglist.c
	${NORMAL_LINT}

subr_sglist.o: $S/kern/subr_sglist.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_sleepqueue.ln: $S/kern/subr_sleepqueue.c
	${NORMAL_LINT}

subr_sleepqueue.o: $S/kern/subr_sleepqueue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_smp.ln: $S/kern/subr_smp.c
	${NORMAL_LINT}

subr_smp.o: $S/kern/subr_smp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_stack.ln: $S/kern/subr_stack.c
	${NORMAL_LINT}

subr_stack.o: $S/kern/subr_stack.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_taskqueue.ln: $S/kern/subr_taskqueue.c
	${NORMAL_LINT}

subr_taskqueue.o: $S/kern/subr_taskqueue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_trap.ln: $S/kern/subr_trap.c
	${NORMAL_LINT}

subr_trap.o: $S/kern/subr_trap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_turnstile.ln: $S/kern/subr_turnstile.c
	${NORMAL_LINT}

subr_turnstile.o: $S/kern/subr_turnstile.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

subr_unit.ln: $S/kern/subr_unit.c
	${NORMAL_LINT}

subr_unit.o: $S/kern/subr_unit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sys_generic.ln: $S/kern/sys_generic.c
	${NORMAL_LINT}

sys_generic.o: $S/kern/sys_generic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sys_pipe.ln: $S/kern/sys_pipe.c
	${NORMAL_LINT}

sys_pipe.o: $S/kern/sys_pipe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sys_process.ln: $S/kern/sys_process.c
	${NORMAL_LINT}

sys_process.o: $S/kern/sys_process.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sys_socket.ln: $S/kern/sys_socket.c
	${NORMAL_LINT}

sys_socket.o: $S/kern/sys_socket.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sysv_ipc.ln: $S/kern/sysv_ipc.c
	${NORMAL_LINT}

sysv_ipc.o: $S/kern/sysv_ipc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sysv_msg.ln: $S/kern/sysv_msg.c
	${NORMAL_LINT}

sysv_msg.o: $S/kern/sysv_msg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sysv_sem.ln: $S/kern/sysv_sem.c
	${NORMAL_LINT}

sysv_sem.o: $S/kern/sysv_sem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sysv_shm.ln: $S/kern/sysv_shm.c
	${NORMAL_LINT}

sysv_shm.o: $S/kern/sysv_shm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty.ln: $S/kern/tty.c
	${NORMAL_LINT}

tty.o: $S/kern/tty.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_compat.ln: $S/kern/tty_compat.c
	${NORMAL_LINT}

tty_compat.o: $S/kern/tty_compat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_info.ln: $S/kern/tty_info.c
	${NORMAL_LINT}

tty_info.o: $S/kern/tty_info.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_inq.ln: $S/kern/tty_inq.c
	${NORMAL_LINT}

tty_inq.o: $S/kern/tty_inq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_outq.ln: $S/kern/tty_outq.c
	${NORMAL_LINT}

tty_outq.o: $S/kern/tty_outq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_pts.ln: $S/kern/tty_pts.c
	${NORMAL_LINT}

tty_pts.o: $S/kern/tty_pts.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_pty.ln: $S/kern/tty_pty.c
	${NORMAL_LINT}

tty_pty.o: $S/kern/tty_pty.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_tty.ln: $S/kern/tty_tty.c
	${NORMAL_LINT}

tty_tty.o: $S/kern/tty_tty.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tty_ttydisc.ln: $S/kern/tty_ttydisc.c
	${NORMAL_LINT}

tty_ttydisc.o: $S/kern/tty_ttydisc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_accf.ln: $S/kern/uipc_accf.c
	${NORMAL_LINT}

uipc_accf.o: $S/kern/uipc_accf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_domain.ln: $S/kern/uipc_domain.c
	${NORMAL_LINT}

uipc_domain.o: $S/kern/uipc_domain.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_mbuf.ln: $S/kern/uipc_mbuf.c
	${NORMAL_LINT}

uipc_mbuf.o: $S/kern/uipc_mbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_mbuf2.ln: $S/kern/uipc_mbuf2.c
	${NORMAL_LINT}

uipc_mbuf2.o: $S/kern/uipc_mbuf2.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_sem.ln: $S/kern/uipc_sem.c
	${NORMAL_LINT}

uipc_sem.o: $S/kern/uipc_sem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_shm.ln: $S/kern/uipc_shm.c
	${NORMAL_LINT}

uipc_shm.o: $S/kern/uipc_shm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_sockbuf.ln: $S/kern/uipc_sockbuf.c
	${NORMAL_LINT}

uipc_sockbuf.o: $S/kern/uipc_sockbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_socket.ln: $S/kern/uipc_socket.c
	${NORMAL_LINT}

uipc_socket.o: $S/kern/uipc_socket.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_syscalls.ln: $S/kern/uipc_syscalls.c
	${NORMAL_LINT}

uipc_syscalls.o: $S/kern/uipc_syscalls.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uipc_usrreq.ln: $S/kern/uipc_usrreq.c
	${NORMAL_LINT}

uipc_usrreq.o: $S/kern/uipc_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_acl.ln: $S/kern/vfs_acl.c
	${NORMAL_LINT}

vfs_acl.o: $S/kern/vfs_acl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_bio.ln: $S/kern/vfs_bio.c
	${NORMAL_LINT}

vfs_bio.o: $S/kern/vfs_bio.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_cache.ln: $S/kern/vfs_cache.c
	${NORMAL_LINT}

vfs_cache.o: $S/kern/vfs_cache.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_cluster.ln: $S/kern/vfs_cluster.c
	${NORMAL_LINT}

vfs_cluster.o: $S/kern/vfs_cluster.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_default.ln: $S/kern/vfs_default.c
	${NORMAL_LINT}

vfs_default.o: $S/kern/vfs_default.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_export.ln: $S/kern/vfs_export.c
	${NORMAL_LINT}

vfs_export.o: $S/kern/vfs_export.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_extattr.ln: $S/kern/vfs_extattr.c
	${NORMAL_LINT}

vfs_extattr.o: $S/kern/vfs_extattr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_hash.ln: $S/kern/vfs_hash.c
	${NORMAL_LINT}

vfs_hash.o: $S/kern/vfs_hash.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_init.ln: $S/kern/vfs_init.c
	${NORMAL_LINT}

vfs_init.o: $S/kern/vfs_init.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_lookup.ln: $S/kern/vfs_lookup.c
	${NORMAL_LINT}

vfs_lookup.o: $S/kern/vfs_lookup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_mount.ln: $S/kern/vfs_mount.c
	${NORMAL_LINT}

vfs_mount.o: $S/kern/vfs_mount.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_subr.ln: $S/kern/vfs_subr.c
	${NORMAL_LINT}

vfs_subr.o: $S/kern/vfs_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_syscalls.ln: $S/kern/vfs_syscalls.c
	${NORMAL_LINT}

vfs_syscalls.o: $S/kern/vfs_syscalls.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vfs_vnops.ln: $S/kern/vfs_vnops.c
	${NORMAL_LINT}

vfs_vnops.o: $S/kern/vfs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

arc4random.ln: $S/libkern/arc4random.c
	${NORMAL_LINT}

arc4random.o: $S/libkern/arc4random.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bcd.ln: $S/libkern/bcd.c
	${NORMAL_LINT}

bcd.o: $S/libkern/bcd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bsearch.ln: $S/libkern/bsearch.c
	${NORMAL_LINT}

bsearch.o: $S/libkern/bsearch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

crc32.ln: $S/libkern/crc32.c
	${NORMAL_LINT}

crc32.o: $S/libkern/crc32.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fnmatch.ln: $S/libkern/fnmatch.c
	${NORMAL_LINT}

fnmatch.o: $S/libkern/fnmatch.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

gets.ln: $S/libkern/gets.c
	${NORMAL_LINT}

gets.o: $S/libkern/gets.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

index.ln: $S/libkern/index.c
	${NORMAL_LINT}

index.o: $S/libkern/index.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

inet_ntoa.ln: $S/libkern/inet_ntoa.c
	${NORMAL_LINT}

inet_ntoa.o: $S/libkern/inet_ntoa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

memcmp.ln: $S/libkern/memcmp.c
	${NORMAL_LINT}

memcmp.o: $S/libkern/memcmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

qsort.ln: $S/libkern/qsort.c
	${NORMAL_LINT}

qsort.o: $S/libkern/qsort.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

qsort_r.ln: $S/libkern/qsort_r.c
	${NORMAL_LINT}

qsort_r.o: $S/libkern/qsort_r.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

random.ln: $S/libkern/random.c
	${NORMAL_LINT}

random.o: $S/libkern/random.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rindex.ln: $S/libkern/rindex.c
	${NORMAL_LINT}

rindex.o: $S/libkern/rindex.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scanc.ln: $S/libkern/scanc.c
	${NORMAL_LINT}

scanc.o: $S/libkern/scanc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

skpc.ln: $S/libkern/skpc.c
	${NORMAL_LINT}

skpc.o: $S/libkern/skpc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strcasecmp.ln: $S/libkern/strcasecmp.c
	${NORMAL_LINT}

strcasecmp.o: $S/libkern/strcasecmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strcat.ln: $S/libkern/strcat.c
	${NORMAL_LINT}

strcat.o: $S/libkern/strcat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strcmp.ln: $S/libkern/strcmp.c
	${NORMAL_LINT}

strcmp.o: $S/libkern/strcmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strcpy.ln: $S/libkern/strcpy.c
	${NORMAL_LINT}

strcpy.o: $S/libkern/strcpy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strcspn.ln: $S/libkern/strcspn.c
	${NORMAL_LINT}

strcspn.o: $S/libkern/strcspn.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strdup.ln: $S/libkern/strdup.c
	${NORMAL_LINT}

strdup.o: $S/libkern/strdup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strlcat.ln: $S/libkern/strlcat.c
	${NORMAL_LINT}

strlcat.o: $S/libkern/strlcat.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strlcpy.ln: $S/libkern/strlcpy.c
	${NORMAL_LINT}

strlcpy.o: $S/libkern/strlcpy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strlen.ln: $S/libkern/strlen.c
	${NORMAL_LINT}

strlen.o: $S/libkern/strlen.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strncmp.ln: $S/libkern/strncmp.c
	${NORMAL_LINT}

strncmp.o: $S/libkern/strncmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strncpy.ln: $S/libkern/strncpy.c
	${NORMAL_LINT}

strncpy.o: $S/libkern/strncpy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strsep.ln: $S/libkern/strsep.c
	${NORMAL_LINT}

strsep.o: $S/libkern/strsep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strspn.ln: $S/libkern/strspn.c
	${NORMAL_LINT}

strspn.o: $S/libkern/strspn.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strstr.ln: $S/libkern/strstr.c
	${NORMAL_LINT}

strstr.o: $S/libkern/strstr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strtol.ln: $S/libkern/strtol.c
	${NORMAL_LINT}

strtol.o: $S/libkern/strtol.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strtoq.ln: $S/libkern/strtoq.c
	${NORMAL_LINT}

strtoq.o: $S/libkern/strtoq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strtoul.ln: $S/libkern/strtoul.c
	${NORMAL_LINT}

strtoul.o: $S/libkern/strtoul.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strtouq.ln: $S/libkern/strtouq.c
	${NORMAL_LINT}

strtouq.o: $S/libkern/strtouq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

strvalid.ln: $S/libkern/strvalid.c
	${NORMAL_LINT}

strvalid.o: $S/libkern/strvalid.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bpf.ln: $S/net/bpf.c
	${NORMAL_LINT}

bpf.o: $S/net/bpf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bpf_buffer.ln: $S/net/bpf_buffer.c
	${NORMAL_LINT}

bpf_buffer.o: $S/net/bpf_buffer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bpf_filter.ln: $S/net/bpf_filter.c
	${NORMAL_LINT}

bpf_filter.o: $S/net/bpf_filter.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bpf_zerocopy.ln: $S/net/bpf_zerocopy.c
	${NORMAL_LINT}

bpf_zerocopy.o: $S/net/bpf_zerocopy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

flowtable.ln: $S/net/flowtable.c
	${NORMAL_LINT}

flowtable.o: $S/net/flowtable.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if.ln: $S/net/if.c
	${NORMAL_LINT}

if.o: $S/net/if.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_clone.ln: $S/net/if_clone.c
	${NORMAL_LINT}

if_clone.o: $S/net/if_clone.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_dead.ln: $S/net/if_dead.c
	${NORMAL_LINT}

if_dead.o: $S/net/if_dead.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ethersubr.ln: $S/net/if_ethersubr.c
	${NORMAL_LINT}

if_ethersubr.o: $S/net/if_ethersubr.c
	${NORMAL_C} -I$S/contrib/pf

if_faith.ln: $S/net/if_faith.c
	${NORMAL_LINT}

if_faith.o: $S/net/if_faith.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fwsubr.ln: $S/net/if_fwsubr.c
	${NORMAL_LINT}

if_fwsubr.o: $S/net/if_fwsubr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_gif.ln: $S/net/if_gif.c
	${NORMAL_LINT}

if_gif.o: $S/net/if_gif.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_loop.ln: $S/net/if_loop.c
	${NORMAL_LINT}

if_loop.o: $S/net/if_loop.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_llatbl.ln: $S/net/if_llatbl.c
	${NORMAL_LINT}

if_llatbl.o: $S/net/if_llatbl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_media.ln: $S/net/if_media.c
	${NORMAL_LINT}

if_media.o: $S/net/if_media.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_mib.ln: $S/net/if_mib.c
	${NORMAL_LINT}

if_mib.o: $S/net/if_mib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_tun.ln: $S/net/if_tun.c
	${NORMAL_LINT}

if_tun.o: $S/net/if_tun.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

netisr.ln: $S/net/netisr.c
	${NORMAL_LINT}

netisr.o: $S/net/netisr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pfil.ln: $S/net/pfil.c
	${NORMAL_LINT}

pfil.o: $S/net/pfil.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

radix.ln: $S/net/radix.c
	${NORMAL_LINT}

radix.o: $S/net/radix.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

radix_mpath.ln: $S/net/radix_mpath.c
	${NORMAL_LINT}

radix_mpath.o: $S/net/radix_mpath.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

raw_cb.ln: $S/net/raw_cb.c
	${NORMAL_LINT}

raw_cb.o: $S/net/raw_cb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

raw_usrreq.ln: $S/net/raw_usrreq.c
	${NORMAL_LINT}

raw_usrreq.o: $S/net/raw_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

route.ln: $S/net/route.c
	${NORMAL_LINT}

route.o: $S/net/route.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rtsock.ln: $S/net/rtsock.c
	${NORMAL_LINT}

rtsock.o: $S/net/rtsock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211.ln: $S/net80211/ieee80211.c
	${NORMAL_LINT}

ieee80211.o: $S/net80211/ieee80211.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_action.ln: $S/net80211/ieee80211_action.c
	${NORMAL_LINT}

ieee80211_action.o: $S/net80211/ieee80211_action.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_ageq.ln: $S/net80211/ieee80211_ageq.c
	${NORMAL_LINT}

ieee80211_ageq.o: $S/net80211/ieee80211_ageq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_adhoc.ln: $S/net80211/ieee80211_adhoc.c
	${NORMAL_LINT}

ieee80211_adhoc.o: $S/net80211/ieee80211_adhoc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_amrr.ln: $S/net80211/ieee80211_amrr.c
	${NORMAL_LINT}

ieee80211_amrr.o: $S/net80211/ieee80211_amrr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_crypto.ln: $S/net80211/ieee80211_crypto.c
	${NORMAL_LINT}

ieee80211_crypto.o: $S/net80211/ieee80211_crypto.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_crypto_ccmp.ln: $S/net80211/ieee80211_crypto_ccmp.c
	${NORMAL_LINT}

ieee80211_crypto_ccmp.o: $S/net80211/ieee80211_crypto_ccmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_crypto_none.ln: $S/net80211/ieee80211_crypto_none.c
	${NORMAL_LINT}

ieee80211_crypto_none.o: $S/net80211/ieee80211_crypto_none.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_crypto_tkip.ln: $S/net80211/ieee80211_crypto_tkip.c
	${NORMAL_LINT}

ieee80211_crypto_tkip.o: $S/net80211/ieee80211_crypto_tkip.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_crypto_wep.ln: $S/net80211/ieee80211_crypto_wep.c
	${NORMAL_LINT}

ieee80211_crypto_wep.o: $S/net80211/ieee80211_crypto_wep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_dfs.ln: $S/net80211/ieee80211_dfs.c
	${NORMAL_LINT}

ieee80211_dfs.o: $S/net80211/ieee80211_dfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_freebsd.ln: $S/net80211/ieee80211_freebsd.c
	${NORMAL_LINT}

ieee80211_freebsd.o: $S/net80211/ieee80211_freebsd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_hostap.ln: $S/net80211/ieee80211_hostap.c
	${NORMAL_LINT}

ieee80211_hostap.o: $S/net80211/ieee80211_hostap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_ht.ln: $S/net80211/ieee80211_ht.c
	${NORMAL_LINT}

ieee80211_ht.o: $S/net80211/ieee80211_ht.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_hwmp.ln: $S/net80211/ieee80211_hwmp.c
	${NORMAL_LINT}

ieee80211_hwmp.o: $S/net80211/ieee80211_hwmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_input.ln: $S/net80211/ieee80211_input.c
	${NORMAL_LINT}

ieee80211_input.o: $S/net80211/ieee80211_input.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_ioctl.ln: $S/net80211/ieee80211_ioctl.c
	${NORMAL_LINT}

ieee80211_ioctl.o: $S/net80211/ieee80211_ioctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_mesh.ln: $S/net80211/ieee80211_mesh.c
	${NORMAL_LINT}

ieee80211_mesh.o: $S/net80211/ieee80211_mesh.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_monitor.ln: $S/net80211/ieee80211_monitor.c
	${NORMAL_LINT}

ieee80211_monitor.o: $S/net80211/ieee80211_monitor.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_node.ln: $S/net80211/ieee80211_node.c
	${NORMAL_LINT}

ieee80211_node.o: $S/net80211/ieee80211_node.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_output.ln: $S/net80211/ieee80211_output.c
	${NORMAL_LINT}

ieee80211_output.o: $S/net80211/ieee80211_output.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_phy.ln: $S/net80211/ieee80211_phy.c
	${NORMAL_LINT}

ieee80211_phy.o: $S/net80211/ieee80211_phy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_power.ln: $S/net80211/ieee80211_power.c
	${NORMAL_LINT}

ieee80211_power.o: $S/net80211/ieee80211_power.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_proto.ln: $S/net80211/ieee80211_proto.c
	${NORMAL_LINT}

ieee80211_proto.o: $S/net80211/ieee80211_proto.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_radiotap.ln: $S/net80211/ieee80211_radiotap.c
	${NORMAL_LINT}

ieee80211_radiotap.o: $S/net80211/ieee80211_radiotap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_regdomain.ln: $S/net80211/ieee80211_regdomain.c
	${NORMAL_LINT}

ieee80211_regdomain.o: $S/net80211/ieee80211_regdomain.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_scan.ln: $S/net80211/ieee80211_scan.c
	${NORMAL_LINT}

ieee80211_scan.o: $S/net80211/ieee80211_scan.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_scan_sta.ln: $S/net80211/ieee80211_scan_sta.c
	${NORMAL_LINT}

ieee80211_scan_sta.o: $S/net80211/ieee80211_scan_sta.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_sta.ln: $S/net80211/ieee80211_sta.c
	${NORMAL_LINT}

ieee80211_sta.o: $S/net80211/ieee80211_sta.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ieee80211_wds.ln: $S/net80211/ieee80211_wds.c
	${NORMAL_LINT}

ieee80211_wds.o: $S/net80211/ieee80211_wds.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ether.ln: $S/netinet/if_ether.c
	${NORMAL_LINT}

if_ether.o: $S/netinet/if_ether.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

igmp.ln: $S/netinet/igmp.c
	${NORMAL_LINT}

igmp.o: $S/netinet/igmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in.ln: $S/netinet/in.c
	${NORMAL_LINT}

in.o: $S/netinet/in.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in_gif.ln: $S/netinet/in_gif.c
	${NORMAL_LINT}

in_gif.o: $S/netinet/in_gif.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_id.ln: $S/netinet/ip_id.c
	${NORMAL_LINT}

ip_id.o: $S/netinet/ip_id.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in_mcast.ln: $S/netinet/in_mcast.c
	${NORMAL_LINT}

in_mcast.o: $S/netinet/in_mcast.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in_pcb.ln: $S/netinet/in_pcb.c
	${NORMAL_LINT}

in_pcb.o: $S/netinet/in_pcb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in_proto.ln: $S/netinet/in_proto.c
	${NORMAL_LINT}

in_proto.o: $S/netinet/in_proto.c
	${NORMAL_C} -I$S/contrib/pf

in_rmx.ln: $S/netinet/in_rmx.c
	${NORMAL_LINT}

in_rmx.o: $S/netinet/in_rmx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_ecn.ln: $S/netinet/ip_ecn.c
	${NORMAL_LINT}

ip_ecn.o: $S/netinet/ip_ecn.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_encap.ln: $S/netinet/ip_encap.c
	${NORMAL_LINT}

ip_encap.o: $S/netinet/ip_encap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_fastfwd.ln: $S/netinet/ip_fastfwd.c
	${NORMAL_LINT}

ip_fastfwd.o: $S/netinet/ip_fastfwd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_icmp.ln: $S/netinet/ip_icmp.c
	${NORMAL_LINT}

ip_icmp.o: $S/netinet/ip_icmp.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_input.ln: $S/netinet/ip_input.c
	${NORMAL_LINT}

ip_input.o: $S/netinet/ip_input.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_options.ln: $S/netinet/ip_options.c
	${NORMAL_LINT}

ip_options.o: $S/netinet/ip_options.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip_output.ln: $S/netinet/ip_output.c
	${NORMAL_LINT}

ip_output.o: $S/netinet/ip_output.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

raw_ip.ln: $S/netinet/raw_ip.c
	${NORMAL_LINT}

raw_ip.o: $S/netinet/raw_ip.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_asconf.ln: $S/netinet/sctp_asconf.c
	${NORMAL_LINT}

sctp_asconf.o: $S/netinet/sctp_asconf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_auth.ln: $S/netinet/sctp_auth.c
	${NORMAL_LINT}

sctp_auth.o: $S/netinet/sctp_auth.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_bsd_addr.ln: $S/netinet/sctp_bsd_addr.c
	${NORMAL_LINT}

sctp_bsd_addr.o: $S/netinet/sctp_bsd_addr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_cc_functions.ln: $S/netinet/sctp_cc_functions.c
	${NORMAL_LINT}

sctp_cc_functions.o: $S/netinet/sctp_cc_functions.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_crc32.ln: $S/netinet/sctp_crc32.c
	${NORMAL_LINT}

sctp_crc32.o: $S/netinet/sctp_crc32.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_indata.ln: $S/netinet/sctp_indata.c
	${NORMAL_LINT}

sctp_indata.o: $S/netinet/sctp_indata.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_input.ln: $S/netinet/sctp_input.c
	${NORMAL_LINT}

sctp_input.o: $S/netinet/sctp_input.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_output.ln: $S/netinet/sctp_output.c
	${NORMAL_LINT}

sctp_output.o: $S/netinet/sctp_output.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_pcb.ln: $S/netinet/sctp_pcb.c
	${NORMAL_LINT}

sctp_pcb.o: $S/netinet/sctp_pcb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_peeloff.ln: $S/netinet/sctp_peeloff.c
	${NORMAL_LINT}

sctp_peeloff.o: $S/netinet/sctp_peeloff.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_sysctl.ln: $S/netinet/sctp_sysctl.c
	${NORMAL_LINT}

sctp_sysctl.o: $S/netinet/sctp_sysctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_timer.ln: $S/netinet/sctp_timer.c
	${NORMAL_LINT}

sctp_timer.o: $S/netinet/sctp_timer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp_usrreq.ln: $S/netinet/sctp_usrreq.c
	${NORMAL_LINT}

sctp_usrreq.o: $S/netinet/sctp_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctputil.ln: $S/netinet/sctputil.c
	${NORMAL_LINT}

sctputil.o: $S/netinet/sctputil.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_hostcache.ln: $S/netinet/tcp_hostcache.c
	${NORMAL_LINT}

tcp_hostcache.o: $S/netinet/tcp_hostcache.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_input.ln: $S/netinet/tcp_input.c
	${NORMAL_LINT}

tcp_input.o: $S/netinet/tcp_input.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_lro.ln: $S/netinet/tcp_lro.c
	${NORMAL_LINT}

tcp_lro.o: $S/netinet/tcp_lro.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_output.ln: $S/netinet/tcp_output.c
	${NORMAL_LINT}

tcp_output.o: $S/netinet/tcp_output.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_offload.ln: $S/netinet/tcp_offload.c
	${NORMAL_LINT}

tcp_offload.o: $S/netinet/tcp_offload.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_reass.ln: $S/netinet/tcp_reass.c
	${NORMAL_LINT}

tcp_reass.o: $S/netinet/tcp_reass.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_sack.ln: $S/netinet/tcp_sack.c
	${NORMAL_LINT}

tcp_sack.o: $S/netinet/tcp_sack.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_subr.ln: $S/netinet/tcp_subr.c
	${NORMAL_LINT}

tcp_subr.o: $S/netinet/tcp_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_syncache.ln: $S/netinet/tcp_syncache.c
	${NORMAL_LINT}

tcp_syncache.o: $S/netinet/tcp_syncache.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_timer.ln: $S/netinet/tcp_timer.c
	${NORMAL_LINT}

tcp_timer.o: $S/netinet/tcp_timer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_timewait.ln: $S/netinet/tcp_timewait.c
	${NORMAL_LINT}

tcp_timewait.o: $S/netinet/tcp_timewait.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tcp_usrreq.ln: $S/netinet/tcp_usrreq.c
	${NORMAL_LINT}

tcp_usrreq.o: $S/netinet/tcp_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

udp_usrreq.ln: $S/netinet/udp_usrreq.c
	${NORMAL_LINT}

udp_usrreq.o: $S/netinet/udp_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dest6.ln: $S/netinet6/dest6.c
	${NORMAL_LINT}

dest6.o: $S/netinet6/dest6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

frag6.ln: $S/netinet6/frag6.c
	${NORMAL_LINT}

frag6.o: $S/netinet6/frag6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

icmp6.ln: $S/netinet6/icmp6.c
	${NORMAL_LINT}

icmp6.o: $S/netinet6/icmp6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6.ln: $S/netinet6/in6.c
	${NORMAL_LINT}

in6.o: $S/netinet6/in6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_cksum.ln: $S/netinet6/in6_cksum.c
	${NORMAL_LINT}

in6_cksum.o: $S/netinet6/in6_cksum.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_gif.ln: $S/netinet6/in6_gif.c
	${NORMAL_LINT}

in6_gif.o: $S/netinet6/in6_gif.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_ifattach.ln: $S/netinet6/in6_ifattach.c
	${NORMAL_LINT}

in6_ifattach.o: $S/netinet6/in6_ifattach.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_mcast.ln: $S/netinet6/in6_mcast.c
	${NORMAL_LINT}

in6_mcast.o: $S/netinet6/in6_mcast.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_pcb.ln: $S/netinet6/in6_pcb.c
	${NORMAL_LINT}

in6_pcb.o: $S/netinet6/in6_pcb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_proto.ln: $S/netinet6/in6_proto.c
	${NORMAL_LINT}

in6_proto.o: $S/netinet6/in6_proto.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_rmx.ln: $S/netinet6/in6_rmx.c
	${NORMAL_LINT}

in6_rmx.o: $S/netinet6/in6_rmx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in6_src.ln: $S/netinet6/in6_src.c
	${NORMAL_LINT}

in6_src.o: $S/netinet6/in6_src.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip6_forward.ln: $S/netinet6/ip6_forward.c
	${NORMAL_LINT}

ip6_forward.o: $S/netinet6/ip6_forward.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip6_id.ln: $S/netinet6/ip6_id.c
	${NORMAL_LINT}

ip6_id.o: $S/netinet6/ip6_id.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip6_input.ln: $S/netinet6/ip6_input.c
	${NORMAL_LINT}

ip6_input.o: $S/netinet6/ip6_input.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ip6_output.ln: $S/netinet6/ip6_output.c
	${NORMAL_LINT}

ip6_output.o: $S/netinet6/ip6_output.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mld6.ln: $S/netinet6/mld6.c
	${NORMAL_LINT}

mld6.o: $S/netinet6/mld6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nd6.ln: $S/netinet6/nd6.c
	${NORMAL_LINT}

nd6.o: $S/netinet6/nd6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nd6_nbr.ln: $S/netinet6/nd6_nbr.c
	${NORMAL_LINT}

nd6_nbr.o: $S/netinet6/nd6_nbr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nd6_rtr.ln: $S/netinet6/nd6_rtr.c
	${NORMAL_LINT}

nd6_rtr.o: $S/netinet6/nd6_rtr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

raw_ip6.ln: $S/netinet6/raw_ip6.c
	${NORMAL_LINT}

raw_ip6.o: $S/netinet6/raw_ip6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

route6.ln: $S/netinet6/route6.c
	${NORMAL_LINT}

route6.o: $S/netinet6/route6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scope6.ln: $S/netinet6/scope6.c
	${NORMAL_LINT}

scope6.o: $S/netinet6/scope6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sctp6_usrreq.ln: $S/netinet6/sctp6_usrreq.c
	${NORMAL_LINT}

sctp6_usrreq.o: $S/netinet6/sctp6_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

udp6_usrreq.ln: $S/netinet6/udp6_usrreq.c
	${NORMAL_LINT}

udp6_usrreq.o: $S/netinet6/udp6_usrreq.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_common.ln: $S/nfs/nfs_common.c
	${NORMAL_LINT}

nfs_common.o: $S/nfs/nfs_common.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_bio.ln: $S/nfsclient/nfs_bio.c
	${NORMAL_LINT}

nfs_bio.o: $S/nfsclient/nfs_bio.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_diskless.ln: $S/nfsclient/nfs_diskless.c
	${NORMAL_LINT}

nfs_diskless.o: $S/nfsclient/nfs_diskless.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_node.ln: $S/nfsclient/nfs_node.c
	${NORMAL_LINT}

nfs_node.o: $S/nfsclient/nfs_node.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_krpc.ln: $S/nfsclient/nfs_krpc.c
	${NORMAL_LINT}

nfs_krpc.o: $S/nfsclient/nfs_krpc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_subs.ln: $S/nfsclient/nfs_subs.c
	${NORMAL_LINT}

nfs_subs.o: $S/nfsclient/nfs_subs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_nfsiod.ln: $S/nfsclient/nfs_nfsiod.c
	${NORMAL_LINT}

nfs_nfsiod.o: $S/nfsclient/nfs_nfsiod.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_vfsops.ln: $S/nfsclient/nfs_vfsops.c
	${NORMAL_LINT}

nfs_vfsops.o: $S/nfsclient/nfs_vfsops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_vnops.ln: $S/nfsclient/nfs_vnops.c
	${NORMAL_LINT}

nfs_vnops.o: $S/nfsclient/nfs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_lock.ln: $S/nfsclient/nfs_lock.c
	${NORMAL_LINT}

nfs_lock.o: $S/nfsclient/nfs_lock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_fha.ln: $S/nfsserver/nfs_fha.c
	${NORMAL_LINT}

nfs_fha.o: $S/nfsserver/nfs_fha.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_serv.ln: $S/nfsserver/nfs_serv.c
	${NORMAL_LINT}

nfs_serv.o: $S/nfsserver/nfs_serv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_srvkrpc.ln: $S/nfsserver/nfs_srvkrpc.c
	${NORMAL_LINT}

nfs_srvkrpc.o: $S/nfsserver/nfs_srvkrpc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_srvsubs.ln: $S/nfsserver/nfs_srvsubs.c
	${NORMAL_LINT}

nfs_srvsubs.o: $S/nfsserver/nfs_srvsubs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nfs_nfssvc.ln: $S/nfs/nfs_nfssvc.c
	${NORMAL_LINT}

nfs_nfssvc.o: $S/nfs/nfs_nfssvc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nlm_advlock.ln: $S/nlm/nlm_advlock.c
	${NORMAL_LINT}

nlm_advlock.o: $S/nlm/nlm_advlock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nlm_prot_clnt.ln: $S/nlm/nlm_prot_clnt.c
	${NORMAL_LINT}

nlm_prot_clnt.o: $S/nlm/nlm_prot_clnt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nlm_prot_impl.ln: $S/nlm/nlm_prot_impl.c
	${NORMAL_LINT}

nlm_prot_impl.o: $S/nlm/nlm_prot_impl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nlm_prot_server.ln: $S/nlm/nlm_prot_server.c
	${NORMAL_LINT}

nlm_prot_server.o: $S/nlm/nlm_prot_server.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nlm_prot_svc.ln: $S/nlm/nlm_prot_svc.c
	${NORMAL_LINT}

nlm_prot_svc.o: $S/nlm/nlm_prot_svc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nlm_prot_xdr.ln: $S/nlm/nlm_prot_xdr.c
	${NORMAL_LINT}

nlm_prot_xdr.o: $S/nlm/nlm_prot_xdr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sm_inter_xdr.ln: $S/nlm/sm_inter_xdr.c
	${NORMAL_LINT}

sm_inter_xdr.o: $S/nlm/sm_inter_xdr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_rl.ln: $S/pci/if_rl.c
	${NORMAL_LINT}

if_rl.o: $S/pci/if_rl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

auth_none.ln: $S/rpc/auth_none.c
	${NORMAL_LINT}

auth_none.o: $S/rpc/auth_none.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

auth_unix.ln: $S/rpc/auth_unix.c
	${NORMAL_LINT}

auth_unix.o: $S/rpc/auth_unix.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

authunix_prot.ln: $S/rpc/authunix_prot.c
	${NORMAL_LINT}

authunix_prot.o: $S/rpc/authunix_prot.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

clnt_dg.ln: $S/rpc/clnt_dg.c
	${NORMAL_LINT}

clnt_dg.o: $S/rpc/clnt_dg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

clnt_rc.ln: $S/rpc/clnt_rc.c
	${NORMAL_LINT}

clnt_rc.o: $S/rpc/clnt_rc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

clnt_vc.ln: $S/rpc/clnt_vc.c
	${NORMAL_LINT}

clnt_vc.o: $S/rpc/clnt_vc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

getnetconfig.ln: $S/rpc/getnetconfig.c
	${NORMAL_LINT}

getnetconfig.o: $S/rpc/getnetconfig.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

inet_ntop.ln: $S/rpc/inet_ntop.c
	${NORMAL_LINT}

inet_ntop.o: $S/rpc/inet_ntop.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

inet_pton.ln: $S/rpc/inet_pton.c
	${NORMAL_LINT}

inet_pton.o: $S/rpc/inet_pton.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

replay.ln: $S/rpc/replay.c
	${NORMAL_LINT}

replay.o: $S/rpc/replay.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rpc_callmsg.ln: $S/rpc/rpc_callmsg.c
	${NORMAL_LINT}

rpc_callmsg.o: $S/rpc/rpc_callmsg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rpc_generic.ln: $S/rpc/rpc_generic.c
	${NORMAL_LINT}

rpc_generic.o: $S/rpc/rpc_generic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rpc_prot.ln: $S/rpc/rpc_prot.c
	${NORMAL_LINT}

rpc_prot.o: $S/rpc/rpc_prot.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rpcb_clnt.ln: $S/rpc/rpcb_clnt.c
	${NORMAL_LINT}

rpcb_clnt.o: $S/rpc/rpcb_clnt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

rpcb_prot.ln: $S/rpc/rpcb_prot.c
	${NORMAL_LINT}

rpcb_prot.o: $S/rpc/rpcb_prot.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

svc.ln: $S/rpc/svc.c
	${NORMAL_LINT}

svc.o: $S/rpc/svc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

svc_auth.ln: $S/rpc/svc_auth.c
	${NORMAL_LINT}

svc_auth.o: $S/rpc/svc_auth.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

svc_auth_unix.ln: $S/rpc/svc_auth_unix.c
	${NORMAL_LINT}

svc_auth_unix.o: $S/rpc/svc_auth_unix.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

svc_dg.ln: $S/rpc/svc_dg.c
	${NORMAL_LINT}

svc_dg.o: $S/rpc/svc_dg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

svc_generic.ln: $S/rpc/svc_generic.c
	${NORMAL_LINT}

svc_generic.o: $S/rpc/svc_generic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

svc_vc.ln: $S/rpc/svc_vc.c
	${NORMAL_LINT}

svc_vc.o: $S/rpc/svc_vc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit.ln: $S/security/audit/audit.c
	${NORMAL_LINT}

audit.o: $S/security/audit/audit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_arg.ln: $S/security/audit/audit_arg.c
	${NORMAL_LINT}

audit_arg.o: $S/security/audit/audit_arg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm.ln: $S/security/audit/audit_bsm.c
	${NORMAL_LINT}

audit_bsm.o: $S/security/audit/audit_bsm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm_domain.ln: $S/security/audit/audit_bsm_domain.c
	${NORMAL_LINT}

audit_bsm_domain.o: $S/security/audit/audit_bsm_domain.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm_errno.ln: $S/security/audit/audit_bsm_errno.c
	${NORMAL_LINT}

audit_bsm_errno.o: $S/security/audit/audit_bsm_errno.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm_fcntl.ln: $S/security/audit/audit_bsm_fcntl.c
	${NORMAL_LINT}

audit_bsm_fcntl.o: $S/security/audit/audit_bsm_fcntl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm_klib.ln: $S/security/audit/audit_bsm_klib.c
	${NORMAL_LINT}

audit_bsm_klib.o: $S/security/audit/audit_bsm_klib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm_socket_type.ln: $S/security/audit/audit_bsm_socket_type.c
	${NORMAL_LINT}

audit_bsm_socket_type.o: $S/security/audit/audit_bsm_socket_type.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_bsm_token.ln: $S/security/audit/audit_bsm_token.c
	${NORMAL_LINT}

audit_bsm_token.o: $S/security/audit/audit_bsm_token.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_pipe.ln: $S/security/audit/audit_pipe.c
	${NORMAL_LINT}

audit_pipe.o: $S/security/audit/audit_pipe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_syscalls.ln: $S/security/audit/audit_syscalls.c
	${NORMAL_LINT}

audit_syscalls.o: $S/security/audit/audit_syscalls.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_trigger.ln: $S/security/audit/audit_trigger.c
	${NORMAL_LINT}

audit_trigger.o: $S/security/audit/audit_trigger.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

audit_worker.ln: $S/security/audit/audit_worker.c
	${NORMAL_LINT}

audit_worker.o: $S/security/audit/audit_worker.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_audit.ln: $S/security/mac/mac_audit.c
	${NORMAL_LINT}

mac_audit.o: $S/security/mac/mac_audit.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_cred.ln: $S/security/mac/mac_cred.c
	${NORMAL_LINT}

mac_cred.o: $S/security/mac/mac_cred.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_framework.ln: $S/security/mac/mac_framework.c
	${NORMAL_LINT}

mac_framework.o: $S/security/mac/mac_framework.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_inet.ln: $S/security/mac/mac_inet.c
	${NORMAL_LINT}

mac_inet.o: $S/security/mac/mac_inet.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_inet6.ln: $S/security/mac/mac_inet6.c
	${NORMAL_LINT}

mac_inet6.o: $S/security/mac/mac_inet6.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_label.ln: $S/security/mac/mac_label.c
	${NORMAL_LINT}

mac_label.o: $S/security/mac/mac_label.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_net.ln: $S/security/mac/mac_net.c
	${NORMAL_LINT}

mac_net.o: $S/security/mac/mac_net.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_pipe.ln: $S/security/mac/mac_pipe.c
	${NORMAL_LINT}

mac_pipe.o: $S/security/mac/mac_pipe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_posix_sem.ln: $S/security/mac/mac_posix_sem.c
	${NORMAL_LINT}

mac_posix_sem.o: $S/security/mac/mac_posix_sem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_posix_shm.ln: $S/security/mac/mac_posix_shm.c
	${NORMAL_LINT}

mac_posix_shm.o: $S/security/mac/mac_posix_shm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_priv.ln: $S/security/mac/mac_priv.c
	${NORMAL_LINT}

mac_priv.o: $S/security/mac/mac_priv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_process.ln: $S/security/mac/mac_process.c
	${NORMAL_LINT}

mac_process.o: $S/security/mac/mac_process.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_socket.ln: $S/security/mac/mac_socket.c
	${NORMAL_LINT}

mac_socket.o: $S/security/mac/mac_socket.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_syscalls.ln: $S/security/mac/mac_syscalls.c
	${NORMAL_LINT}

mac_syscalls.o: $S/security/mac/mac_syscalls.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_system.ln: $S/security/mac/mac_system.c
	${NORMAL_LINT}

mac_system.o: $S/security/mac/mac_system.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_sysv_msg.ln: $S/security/mac/mac_sysv_msg.c
	${NORMAL_LINT}

mac_sysv_msg.o: $S/security/mac/mac_sysv_msg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_sysv_sem.ln: $S/security/mac/mac_sysv_sem.c
	${NORMAL_LINT}

mac_sysv_sem.o: $S/security/mac/mac_sysv_sem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_sysv_shm.ln: $S/security/mac/mac_sysv_shm.c
	${NORMAL_LINT}

mac_sysv_shm.o: $S/security/mac/mac_sysv_shm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mac_vfs.ln: $S/security/mac/mac_vfs.c
	${NORMAL_LINT}

mac_vfs.o: $S/security/mac/mac_vfs.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_alloc.ln: $S/ufs/ffs/ffs_alloc.c
	${NORMAL_LINT}

ffs_alloc.o: $S/ufs/ffs/ffs_alloc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_balloc.ln: $S/ufs/ffs/ffs_balloc.c
	${NORMAL_LINT}

ffs_balloc.o: $S/ufs/ffs/ffs_balloc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_inode.ln: $S/ufs/ffs/ffs_inode.c
	${NORMAL_LINT}

ffs_inode.o: $S/ufs/ffs/ffs_inode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_snapshot.ln: $S/ufs/ffs/ffs_snapshot.c
	${NORMAL_LINT}

ffs_snapshot.o: $S/ufs/ffs/ffs_snapshot.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_softdep.ln: $S/ufs/ffs/ffs_softdep.c
	${NORMAL_LINT}

ffs_softdep.o: $S/ufs/ffs/ffs_softdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_subr.ln: $S/ufs/ffs/ffs_subr.c
	${NORMAL_LINT}

ffs_subr.o: $S/ufs/ffs/ffs_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_tables.ln: $S/ufs/ffs/ffs_tables.c
	${NORMAL_LINT}

ffs_tables.o: $S/ufs/ffs/ffs_tables.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_vfsops.ln: $S/ufs/ffs/ffs_vfsops.c
	${NORMAL_LINT}

ffs_vfsops.o: $S/ufs/ffs/ffs_vfsops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffs_vnops.ln: $S/ufs/ffs/ffs_vnops.c
	${NORMAL_LINT}

ffs_vnops.o: $S/ufs/ffs/ffs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_acl.ln: $S/ufs/ufs/ufs_acl.c
	${NORMAL_LINT}

ufs_acl.o: $S/ufs/ufs/ufs_acl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_bmap.ln: $S/ufs/ufs/ufs_bmap.c
	${NORMAL_LINT}

ufs_bmap.o: $S/ufs/ufs/ufs_bmap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_dirhash.ln: $S/ufs/ufs/ufs_dirhash.c
	${NORMAL_LINT}

ufs_dirhash.o: $S/ufs/ufs/ufs_dirhash.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_extattr.ln: $S/ufs/ufs/ufs_extattr.c
	${NORMAL_LINT}

ufs_extattr.o: $S/ufs/ufs/ufs_extattr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_gjournal.ln: $S/ufs/ufs/ufs_gjournal.c
	${NORMAL_LINT}

ufs_gjournal.o: $S/ufs/ufs/ufs_gjournal.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_inode.ln: $S/ufs/ufs/ufs_inode.c
	${NORMAL_LINT}

ufs_inode.o: $S/ufs/ufs/ufs_inode.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_lookup.ln: $S/ufs/ufs/ufs_lookup.c
	${NORMAL_LINT}

ufs_lookup.o: $S/ufs/ufs/ufs_lookup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_quota.ln: $S/ufs/ufs/ufs_quota.c
	${NORMAL_LINT}

ufs_quota.o: $S/ufs/ufs/ufs_quota.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_vfsops.ln: $S/ufs/ufs/ufs_vfsops.c
	${NORMAL_LINT}

ufs_vfsops.o: $S/ufs/ufs/ufs_vfsops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ufs_vnops.ln: $S/ufs/ufs/ufs_vnops.c
	${NORMAL_LINT}

ufs_vnops.o: $S/ufs/ufs/ufs_vnops.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

default_pager.ln: $S/vm/default_pager.c
	${NORMAL_LINT}

default_pager.o: $S/vm/default_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

device_pager.ln: $S/vm/device_pager.c
	${NORMAL_LINT}

device_pager.o: $S/vm/device_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

phys_pager.ln: $S/vm/phys_pager.c
	${NORMAL_LINT}

phys_pager.o: $S/vm/phys_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sg_pager.ln: $S/vm/sg_pager.c
	${NORMAL_LINT}

sg_pager.o: $S/vm/sg_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

swap_pager.ln: $S/vm/swap_pager.c
	${NORMAL_LINT}

swap_pager.o: $S/vm/swap_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uma_core.ln: $S/vm/uma_core.c
	${NORMAL_LINT}

uma_core.o: $S/vm/uma_core.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uma_dbg.ln: $S/vm/uma_dbg.c
	${NORMAL_LINT}

uma_dbg.o: $S/vm/uma_dbg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_contig.ln: $S/vm/vm_contig.c
	${NORMAL_LINT}

vm_contig.o: $S/vm/vm_contig.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_fault.ln: $S/vm/vm_fault.c
	${NORMAL_LINT}

vm_fault.o: $S/vm/vm_fault.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_glue.ln: $S/vm/vm_glue.c
	${NORMAL_LINT}

vm_glue.o: $S/vm/vm_glue.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_init.ln: $S/vm/vm_init.c
	${NORMAL_LINT}

vm_init.o: $S/vm/vm_init.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_kern.ln: $S/vm/vm_kern.c
	${NORMAL_LINT}

vm_kern.o: $S/vm/vm_kern.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_map.ln: $S/vm/vm_map.c
	${NORMAL_LINT}

vm_map.o: $S/vm/vm_map.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_meter.ln: $S/vm/vm_meter.c
	${NORMAL_LINT}

vm_meter.o: $S/vm/vm_meter.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_mmap.ln: $S/vm/vm_mmap.c
	${NORMAL_LINT}

vm_mmap.o: $S/vm/vm_mmap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_object.ln: $S/vm/vm_object.c
	${NORMAL_LINT}

vm_object.o: $S/vm/vm_object.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_page.ln: $S/vm/vm_page.c
	${NORMAL_LINT}

vm_page.o: $S/vm/vm_page.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_pageout.ln: $S/vm/vm_pageout.c
	${NORMAL_LINT}

vm_pageout.o: $S/vm/vm_pageout.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_pager.ln: $S/vm/vm_pager.c
	${NORMAL_LINT}

vm_pager.o: $S/vm/vm_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_phys.ln: $S/vm/vm_phys.c
	${NORMAL_LINT}

vm_phys.o: $S/vm/vm_phys.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_reserv.ln: $S/vm/vm_reserv.c
	${NORMAL_LINT}

vm_reserv.o: $S/vm/vm_reserv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_unix.ln: $S/vm/vm_unix.c
	${NORMAL_LINT}

vm_unix.o: $S/vm/vm_unix.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_zeroidle.ln: $S/vm/vm_zeroidle.c
	${NORMAL_LINT}

vm_zeroidle.o: $S/vm/vm_zeroidle.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vnode_pager.ln: $S/vm/vnode_pager.c
	${NORMAL_LINT}

vnode_pager.o: $S/vm/vnode_pager.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xdr.ln: $S/xdr/xdr.c
	${NORMAL_LINT}

xdr.o: $S/xdr/xdr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xdr_array.ln: $S/xdr/xdr_array.c
	${NORMAL_LINT}

xdr_array.o: $S/xdr/xdr_array.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xdr_mbuf.ln: $S/xdr/xdr_mbuf.c
	${NORMAL_LINT}

xdr_mbuf.o: $S/xdr/xdr_mbuf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xdr_mem.ln: $S/xdr/xdr_mem.c
	${NORMAL_LINT}

xdr_mem.o: $S/xdr/xdr_mem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xdr_reference.ln: $S/xdr/xdr_reference.c
	${NORMAL_LINT}

xdr_reference.o: $S/xdr/xdr_reference.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

xdr_sizeof.ln: $S/xdr/xdr_sizeof.c
	${NORMAL_LINT}

xdr_sizeof.o: $S/xdr/xdr_sizeof.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hptmvraid.o: $S/dev/hptmv/i386-elf.raid.o.uu
	uudecode < $S/dev/hptmv/i386-elf.raid.o.uu

hptrr_lib.o: $S/dev/hptrr/i386-elf.hptrr_lib.o.uu
	uudecode < $S/dev/hptrr/i386-elf.hptrr_lib.o.uu

adv_isa.ln: $S/dev/advansys/adv_isa.c
	${NORMAL_LINT}

adv_isa.o: $S/dev/advansys/adv_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_ali.ln: $S/dev/agp/agp_ali.c
	${NORMAL_LINT}

agp_ali.o: $S/dev/agp/agp_ali.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_amd.ln: $S/dev/agp/agp_amd.c
	${NORMAL_LINT}

agp_amd.o: $S/dev/agp/agp_amd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_amd64.ln: $S/dev/agp/agp_amd64.c
	${NORMAL_LINT}

agp_amd64.o: $S/dev/agp/agp_amd64.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_ati.ln: $S/dev/agp/agp_ati.c
	${NORMAL_LINT}

agp_ati.o: $S/dev/agp/agp_ati.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_i810.ln: $S/dev/agp/agp_i810.c
	${NORMAL_LINT}

agp_i810.o: $S/dev/agp/agp_i810.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_intel.ln: $S/dev/agp/agp_intel.c
	${NORMAL_LINT}

agp_intel.o: $S/dev/agp/agp_intel.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_nvidia.ln: $S/dev/agp/agp_nvidia.c
	${NORMAL_LINT}

agp_nvidia.o: $S/dev/agp/agp_nvidia.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_sis.ln: $S/dev/agp/agp_sis.c
	${NORMAL_LINT}

agp_sis.o: $S/dev/agp/agp_sis.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

agp_via.ln: $S/dev/agp/agp_via.c
	${NORMAL_LINT}

agp_via.o: $S/dev/agp/agp_via.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

aic_isa.ln: $S/dev/aic/aic_isa.c
	${NORMAL_LINT}

aic_isa.o: $S/dev/aic/aic_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

arcmsr.ln: $S/dev/arcmsr/arcmsr.c
	${NORMAL_LINT}

arcmsr.o: $S/dev/arcmsr/arcmsr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atkbd.ln: $S/dev/atkbdc/atkbd.c
	${NORMAL_LINT}

atkbd.o: $S/dev/atkbdc/atkbd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atkbd_atkbdc.ln: $S/dev/atkbdc/atkbd_atkbdc.c
	${NORMAL_LINT}

atkbd_atkbdc.o: $S/dev/atkbdc/atkbd_atkbdc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atkbdc.ln: $S/dev/atkbdc/atkbdc.c
	${NORMAL_LINT}

atkbdc.o: $S/dev/atkbdc/atkbdc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atkbdc_isa.ln: $S/dev/atkbdc/atkbdc_isa.c
	${NORMAL_LINT}

atkbdc_isa.o: $S/dev/atkbdc/atkbdc_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atkbdc_subr.ln: $S/dev/atkbdc/atkbdc_subr.c
	${NORMAL_LINT}

atkbdc_subr.o: $S/dev/atkbdc/atkbdc_subr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

psm.ln: $S/dev/atkbdc/psm.c
	${NORMAL_LINT}

psm.o: $S/dev/atkbdc/psm.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed_isa.ln: $S/dev/ed/if_ed_isa.c
	${NORMAL_LINT}

if_ed_isa.o: $S/dev/ed/if_ed_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_ed_wd80x3.ln: $S/dev/ed/if_ed_wd80x3.c
	${NORMAL_LINT}

if_ed_wd80x3.o: $S/dev/ed/if_ed_wd80x3.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fb.ln: $S/dev/fb/fb.c
	${NORMAL_LINT}

fb.o: $S/dev/fb/fb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vga.ln: $S/dev/fb/vga.c
	${NORMAL_LINT}

vga.o: $S/dev/fb/vga.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fdc.ln: $S/dev/fdc/fdc.c
	${NORMAL_LINT}

fdc.o: $S/dev/fdc/fdc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fdc_acpi.ln: $S/dev/fdc/fdc_acpi.c
	${NORMAL_LINT}

fdc_acpi.o: $S/dev/fdc/fdc_acpi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fdc_isa.ln: $S/dev/fdc/fdc_isa.c
	${NORMAL_LINT}

fdc_isa.o: $S/dev/fdc/fdc_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

fdc_pccard.ln: $S/dev/fdc/fdc_pccard.c
	${NORMAL_LINT}

fdc_pccard.o: $S/dev/fdc/fdc_pccard.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_fe_isa.ln: $S/dev/fe/if_fe_isa.c
	${NORMAL_LINT}

if_fe_isa.o: $S/dev/fe/if_fe_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

entry.ln: $S/dev/hptmv/entry.c
	${NORMAL_LINT}

entry.o: $S/dev/hptmv/entry.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mv.ln: $S/dev/hptmv/mv.c
	${NORMAL_LINT}

mv.o: $S/dev/hptmv/mv.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

gui_lib.ln: $S/dev/hptmv/gui_lib.c
	${NORMAL_LINT}

gui_lib.o: $S/dev/hptmv/gui_lib.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hptproc.ln: $S/dev/hptmv/hptproc.c
	${NORMAL_LINT}

hptproc.o: $S/dev/hptmv/hptproc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ioctl.ln: $S/dev/hptmv/ioctl.c
	${NORMAL_LINT}

ioctl.o: $S/dev/hptmv/ioctl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hptrr_os_bsd.ln: $S/dev/hptrr/hptrr_os_bsd.c
	${NORMAL_LINT}

hptrr_os_bsd.o: $S/dev/hptrr/hptrr_os_bsd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hptrr_osm_bsd.ln: $S/dev/hptrr/hptrr_osm_bsd.c
	${NORMAL_LINT}

hptrr_osm_bsd.o: $S/dev/hptrr/hptrr_osm_bsd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hptrr_config.ln: $S/dev/hptrr/hptrr_config.c
	${NORMAL_LINT}

hptrr_config.o: $S/dev/hptrr/hptrr_config.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

iodev.ln: $S/dev/io/iodev.c
	${NORMAL_LINT}

iodev.o: $S/dev/io/iodev.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

kbd.ln: $S/dev/kbd/kbd.c
	${NORMAL_LINT}

kbd.o: $S/dev/kbd/kbd.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_le_isa.ln: $S/dev/le/if_le_isa.c
	${NORMAL_LINT}

if_le_isa.o: $S/dev/le/if_le_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

memutil.ln: $S/dev/mem/memutil.c
	${NORMAL_LINT}

memutil.o: $S/dev/mem/memutil.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

if_nfe.ln: $S/dev/nfe/if_nfe.c
	${NORMAL_LINT}

if_nfe.o: $S/dev/nfe/if_nfe.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nehemiah.ln: $S/dev/random/nehemiah.c
	${NORMAL_LINT}

nehemiah.o: $S/dev/random/nehemiah.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scterm-teken.ln: $S/dev/syscons/scterm-teken.c
	${NORMAL_LINT}

scterm-teken.o: $S/dev/syscons/scterm-teken.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scvgarndr.ln: $S/dev/syscons/scvgarndr.c
	${NORMAL_LINT}

scvgarndr.o: $S/dev/syscons/scvgarndr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

scvtb.ln: $S/dev/syscons/scvtb.c
	${NORMAL_LINT}

scvtb.o: $S/dev/syscons/scvtb.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

teken.ln: $S/dev/syscons/teken/teken.c
	${NORMAL_LINT}

teken.o: $S/dev/syscons/teken/teken.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uart_cpu_i386.ln: $S/dev/uart/uart_cpu_i386.c
	${NORMAL_LINT}

uart_cpu_i386.o: $S/dev/uart/uart_cpu_i386.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_if.ln: $S/dev/acpica/acpi_if.m
	${NORMAL_LINT}

acpi_if.o: $S/dev/acpica/acpi_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_wmi_if.ln: $S/dev/acpi_support/acpi_wmi_if.m
	${NORMAL_LINT}

acpi_wmi_if.o: $S/dev/acpi_support/acpi_wmi_if.m
	${NORMAL_M}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

OsdEnvironment.ln: $S/i386/acpica/OsdEnvironment.c
	${NORMAL_LINT}

OsdEnvironment.o: $S/i386/acpica/OsdEnvironment.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_machdep.ln: $S/i386/acpica/acpi_machdep.c
	${NORMAL_LINT}

acpi_machdep.o: $S/i386/acpica/acpi_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_wakeup.ln: $S/i386/acpica/acpi_wakeup.c
	${NORMAL_LINT}

acpi_wakeup.o: $S/i386/acpica/acpi_wakeup.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

acpi_wakecode.h: $S/i386/acpica/acpi_wakecode.S assym.s
	${MAKE} -f $S/i386/acpica/Makefile MAKESRCPATH=$S/i386/acpica

madt.ln: $S/i386/acpica/madt.c
	${NORMAL_LINT}

madt.o: $S/i386/acpica/madt.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

est.ln: $S/i386/cpufreq/est.c
	${NORMAL_LINT}

est.o: $S/i386/cpufreq/est.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

hwpstate.ln: $S/i386/cpufreq/hwpstate.c
	${NORMAL_LINT}

hwpstate.o: $S/i386/cpufreq/hwpstate.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

p4tcc.ln: $S/i386/cpufreq/p4tcc.c
	${NORMAL_LINT}

p4tcc.o: $S/i386/cpufreq/p4tcc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

powernow.ln: $S/i386/cpufreq/powernow.c
	${NORMAL_LINT}

powernow.o: $S/i386/cpufreq/powernow.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

smist.ln: $S/i386/cpufreq/smist.c
	${NORMAL_LINT}

smist.o: $S/i386/cpufreq/smist.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atomic.ln: $S/i386/i386/atomic.c
	${NORMAL_LINT}

atomic.o: $S/i386/i386/atomic.c
	${CC} -c ${CFLAGS} ${DEFINED_PROF:S/^$/-fomit-frame-pointer/} ${.IMPSRC}

autoconf.ln: $S/i386/i386/autoconf.c
	${NORMAL_LINT}

autoconf.o: $S/i386/i386/autoconf.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bios.ln: $S/i386/i386/bios.c
	${NORMAL_LINT}

bios.o: $S/i386/i386/bios.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

bioscall.ln: $S/i386/i386/bioscall.s
	${NORMAL_LINT}

bioscall.o: $S/i386/i386/bioscall.s
	${NORMAL_S}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

busdma_machdep.ln: $S/i386/i386/busdma_machdep.c
	${NORMAL_LINT}

busdma_machdep.o: $S/i386/i386/busdma_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

dump_machdep.ln: $S/i386/i386/dump_machdep.c
	${NORMAL_LINT}

dump_machdep.o: $S/i386/i386/dump_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

elf_machdep.ln: $S/i386/i386/elf_machdep.c
	${NORMAL_LINT}

elf_machdep.o: $S/i386/i386/elf_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

exception.ln: $S/i386/i386/exception.s
	${NORMAL_LINT}

exception.o: $S/i386/i386/exception.s
	${NORMAL_S}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

i686_mem.ln: $S/i386/i386/i686_mem.c
	${NORMAL_LINT}

i686_mem.o: $S/i386/i386/i686_mem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

identcpu.ln: $S/i386/i386/identcpu.c
	${NORMAL_LINT}

identcpu.o: $S/i386/i386/identcpu.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

in_cksum.ln: $S/i386/i386/in_cksum.c
	${NORMAL_LINT}

in_cksum.o: $S/i386/i386/in_cksum.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

initcpu.ln: $S/i386/i386/initcpu.c
	${NORMAL_LINT}

initcpu.o: $S/i386/i386/initcpu.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

intr_machdep.ln: $S/i386/i386/intr_machdep.c
	${NORMAL_LINT}

intr_machdep.o: $S/i386/i386/intr_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

io.ln: $S/i386/i386/io.c
	${NORMAL_LINT}

io.o: $S/i386/i386/io.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

io_apic.ln: $S/i386/i386/io_apic.c
	${NORMAL_LINT}

io_apic.o: $S/i386/i386/io_apic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

k6_mem.ln: $S/i386/i386/k6_mem.c
	${NORMAL_LINT}

k6_mem.o: $S/i386/i386/k6_mem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

legacy.ln: $S/i386/i386/legacy.c
	${NORMAL_LINT}

legacy.o: $S/i386/i386/legacy.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

local_apic.ln: $S/i386/i386/local_apic.c
	${NORMAL_LINT}

local_apic.o: $S/i386/i386/local_apic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

locore.ln: $S/i386/i386/locore.s
	${NORMAL_LINT}

locore.o: $S/i386/i386/locore.s
	${NORMAL_S}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

machdep.ln: $S/i386/i386/machdep.c
	${NORMAL_LINT}

machdep.o: $S/i386/i386/machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mca.ln: $S/i386/i386/mca.c
	${NORMAL_LINT}

mca.o: $S/i386/i386/mca.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mem.ln: $S/i386/i386/mem.c
	${NORMAL_LINT}

mem.o: $S/i386/i386/mem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

minidump_machdep.ln: $S/i386/i386/minidump_machdep.c
	${NORMAL_LINT}

minidump_machdep.o: $S/i386/i386/minidump_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mp_clock.ln: $S/i386/i386/mp_clock.c
	${NORMAL_LINT}

mp_clock.o: $S/i386/i386/mp_clock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mp_machdep.ln: $S/i386/i386/mp_machdep.c
	${NORMAL_LINT}

mp_machdep.o: $S/i386/i386/mp_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mpboot.ln: $S/i386/i386/mpboot.s
	${NORMAL_LINT}

mpboot.o: $S/i386/i386/mpboot.s
	${NORMAL_S}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mptable.ln: $S/i386/i386/mptable.c
	${NORMAL_LINT}

mptable.o: $S/i386/i386/mptable.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

mptable_pci.ln: $S/i386/i386/mptable_pci.c
	${NORMAL_LINT}

mptable_pci.o: $S/i386/i386/mptable_pci.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

msi.ln: $S/i386/i386/msi.c
	${NORMAL_LINT}

msi.o: $S/i386/i386/msi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nexus.ln: $S/i386/i386/nexus.c
	${NORMAL_LINT}

nexus.o: $S/i386/i386/nexus.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pmap.ln: $S/i386/i386/pmap.c
	${NORMAL_LINT}

pmap.o: $S/i386/i386/pmap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ptrace_machdep.ln: $S/i386/i386/ptrace_machdep.c
	${NORMAL_LINT}

ptrace_machdep.o: $S/i386/i386/ptrace_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

stack_machdep.ln: $S/i386/i386/stack_machdep.c
	${NORMAL_LINT}

stack_machdep.o: $S/i386/i386/stack_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

support.ln: $S/i386/i386/support.s
	${NORMAL_LINT}

support.o: $S/i386/i386/support.s
	${NORMAL_S}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

swtch.ln: $S/i386/i386/swtch.s
	${NORMAL_LINT}

swtch.o: $S/i386/i386/swtch.s
	${NORMAL_S}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

sys_machdep.ln: $S/i386/i386/sys_machdep.c
	${NORMAL_LINT}

sys_machdep.o: $S/i386/i386/sys_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

trap.ln: $S/i386/i386/trap.c
	${NORMAL_LINT}

trap.o: $S/i386/i386/trap.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

tsc.ln: $S/i386/i386/tsc.c
	${NORMAL_LINT}

tsc.o: $S/i386/i386/tsc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

uio_machdep.ln: $S/i386/i386/uio_machdep.c
	${NORMAL_LINT}

uio_machdep.o: $S/i386/i386/uio_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm86.ln: $S/i386/i386/vm86.c
	${NORMAL_LINT}

vm86.o: $S/i386/i386/vm86.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vm_machdep.ln: $S/i386/i386/vm_machdep.c
	${NORMAL_LINT}

vm_machdep.o: $S/i386/i386/vm_machdep.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atpic.ln: $S/i386/isa/atpic.c
	${NORMAL_LINT}

atpic.o: $S/i386/isa/atpic.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

clock.ln: $S/i386/isa/clock.c
	${NORMAL_LINT}

clock.o: $S/i386/isa/clock.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

elcr.ln: $S/i386/isa/elcr.c
	${NORMAL_LINT}

elcr.o: $S/i386/isa/elcr.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

elink.ln: $S/i386/isa/elink.c
	${NORMAL_LINT}

elink.o: $S/i386/isa/elink.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isa.ln: $S/i386/isa/isa.c
	${NORMAL_LINT}

isa.o: $S/i386/isa/isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

isa_dma.ln: $S/i386/isa/isa_dma.c
	${NORMAL_LINT}

isa_dma.o: $S/i386/isa/isa_dma.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

nmi.ln: $S/i386/isa/nmi.c
	${NORMAL_LINT}

nmi.o: $S/i386/isa/nmi.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

npx.ln: $S/i386/isa/npx.c
	${NORMAL_LINT}

npx.o: $S/i386/isa/npx.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pmtimer.ln: $S/i386/isa/pmtimer.c
	${NORMAL_LINT}

pmtimer.o: $S/i386/isa/pmtimer.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci_bus.ln: $S/i386/pci/pci_bus.c
	${NORMAL_LINT}

pci_bus.o: $S/i386/pci/pci_bus.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci_cfgreg.ln: $S/i386/pci/pci_cfgreg.c
	${NORMAL_LINT}

pci_cfgreg.o: $S/i386/pci/pci_cfgreg.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

pci_pir.ln: $S/i386/pci/pci_pir.c
	${NORMAL_LINT}

pci_pir.o: $S/i386/pci/pci_pir.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

atrtc.ln: $S/isa/atrtc.c
	${NORMAL_LINT}

atrtc.o: $S/isa/atrtc.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

syscons_isa.ln: $S/isa/syscons_isa.c
	${NORMAL_LINT}

syscons_isa.o: $S/isa/syscons_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

vga_isa.ln: $S/isa/vga_isa.c
	${NORMAL_LINT}

vga_isa.o: $S/isa/vga_isa.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

divdi3.ln: $S/libkern/divdi3.c
	${NORMAL_LINT}

divdi3.o: $S/libkern/divdi3.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ffsl.ln: $S/libkern/ffsl.c
	${NORMAL_LINT}

ffsl.o: $S/libkern/ffsl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

flsl.ln: $S/libkern/flsl.c
	${NORMAL_LINT}

flsl.o: $S/libkern/flsl.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

memmove.ln: $S/libkern/memmove.c
	${NORMAL_LINT}

memmove.o: $S/libkern/memmove.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

memset.ln: $S/libkern/memset.c
	${NORMAL_LINT}

memset.o: $S/libkern/memset.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

moddi3.ln: $S/libkern/moddi3.c
	${NORMAL_LINT}

moddi3.o: $S/libkern/moddi3.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

qdivrem.ln: $S/libkern/qdivrem.c
	${NORMAL_LINT}

qdivrem.o: $S/libkern/qdivrem.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

ucmpdi2.ln: $S/libkern/ucmpdi2.c
	${NORMAL_LINT}

ucmpdi2.o: $S/libkern/ucmpdi2.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

udivdi3.ln: $S/libkern/udivdi3.c
	${NORMAL_LINT}

udivdi3.o: $S/libkern/udivdi3.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif

umoddi3.ln: $S/libkern/umoddi3.c
	${NORMAL_LINT}

umoddi3.o: $S/libkern/umoddi3.c
	${NORMAL_C}
.if defined(NORMAL_CTFCONVERT) && !empty(NORMAL_CTFCONVERT)
	${NORMAL_CTFCONVERT}
.endif


.include "$S/conf/kern.post.mk"
