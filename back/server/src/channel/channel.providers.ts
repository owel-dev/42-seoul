import { DataSource } from "typeorm";
import { ChannelEntity } from "./entities/channel.entity";

export const channelProviders = [
	{
		provide: "CHANNEL_REPOSITORY",
		useFactory: (dataSource: DataSource) => dataSource.getRepository(ChannelEntity),
		inject: ['DATA_SOURCE'],
	}
];