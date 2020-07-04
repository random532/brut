# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.12
CATEGORIES=	sysutils

MAINTAINER=	georg.lastname@web.de
COMMENT=	GUI for editing hard drives (partition editor), uses gtk3

LICENSE=	BSD2CLAUSE

USE_GITHUB=	yes
GH_ACCOUNT=	random532

USES=		gnome
USE_GNOME=	gtk30

PLIST_FILES=	bin/xdisk

do-install:
	${INSTALL_PROGRAM} work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}${LOCALBASE}/bin

.include <bsd.port.mk>
