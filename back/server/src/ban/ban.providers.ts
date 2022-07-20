import { DataSource } from "typeorm";
import { Ban } from "./entities/ban.entity";

export const banProviders = [
	{
		provide: "BAN_REPOSITORY",
		useFactory: (dataSource: DataSource) => dataSource.getRepository(Ban),
		inject: ['DATA_SOURCE'],
	}
];