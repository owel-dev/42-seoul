import { Friend } from "src/friend/entities/friend.entity";
import { Match } from "src/match/entities/match.entity";
import { Stat } from "src/stats/entities/stat.entity";
import { Column, Entity, OneToMany, OneToOne, PrimaryColumn } from "typeorm";

@Entity('users')
export class User {
	@PrimaryColumn()
	intra_id: string;

	@Column()
	nickname: string;

	@Column()
	intra_email: string;

	@Column()
	avatar: string;

	@Column()
	status: string;

	@Column()
	role: string;

	@Column()
	channel_id: string;

	@OneToOne(() => Stat, (stat) => stat.user, {
		cascade: true,
	})
	stats: Stat;

	@OneToMany(() => Match, (match) => match.player_1)
	matches_1: Match[];

	@OneToMany(() => Match, (match) => match.player_2)
	matches_2: Match[];

	@OneToMany(() => Friend, (match) => match.friend_1)
	frined_1: Friend[];

	@OneToMany(() => Friend, (match) => match.friend_2)
	frined_2: Friend[];
}
