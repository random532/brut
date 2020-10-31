# $FreeBSD$

PORTNAME=	xdisk
DISTVERSION=	1.40
CATEGORIES=	sysutils

MAINTAINER=	georg.lastname@web.de
COMMENT=	Partition editor with GUI, manage groups/user

LICENSE=	BSD2CLAUSE

RUN_DEPENDS=	sudo>0:security/sudo

USES=		gnome
USE_GNOME=	gtk30

USE_GITHUB=	yes
GH_ACCOUNT=	random532

PLIST_FILES=	bin/xdisk

do-install:
	${INSTALL_PROGRAM} work/${PORTNAME}-${DISTVERSION}/${PORTNAME} ${STAGEDIR}${LOCALBASE}/bin

.include <bsd.port.mk>
