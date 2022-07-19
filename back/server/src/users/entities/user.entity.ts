import { Ban } from "src/ban/entities/ban.entity";
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

	@OneToMany(() => Friend, (friend) => friend.friend_1)
	friend_1: Friend[];

	@OneToMany(() => Friend, (friend) => friend.friend_2)
	friend_2: Friend[];

	@OneToMany(() => Ban, (ban) => ban.ban_1)
	ban_1: Ban[];

	@OneToMany(() => Ban, (ban) => ban.ban_2)
	ban_2: Ban[];
}
