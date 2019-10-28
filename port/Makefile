# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.0
CATEGORIES=	sysutils
MASTER_SITES=	https://raw.githubusercontent.com/random532/partition-editor-FreeBSD/master/port/
MAINTAINER=	georg.lastname@web.de
COMMENT=	Partition Editor with GUI, create file systems, write .iso
#USES=		xorg
USE_XORG=	x11 xt
#LIB_DEPENDS=
#BUILD_DEPENS=
RUN_DEPENDS=	${LOCALBASE}/sbin/mkntfs:/devel/libfsntfs-e

do-install:
	install -g wheel -m 0755 -o root work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}/${LOCALBASE}/bin

.include <bsd.port.mk>
